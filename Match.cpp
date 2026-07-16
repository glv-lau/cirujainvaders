#include "Match.h"
#include "Game.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>

Match::Match()
    : m_rng(std::random_device{}())
{
    if (!m_playerTex.loadFromFile("Nave.png")) {
        std::cerr << "Error: no se pudo cargar Nave.png\n";
    }
    if (!m_enemyTex.loadFromFile("Nave.png")) {
        std::cerr << "Error: no se pudo cargar textura de enemigo\n";
    }

    sf::Image bulletImg;
    bulletImg.create(4, 4, sf::Color::Yellow);
    if (!m_bulletTex.loadFromImage(bulletImg)) {
        std::cerr << "Error: no se pudo crear textura de bala\n";
    }

    sf::Image powerUpImg;
    powerUpImg.create(12, 12, sf::Color::White);
    if (!m_powerUpTex.loadFromImage(powerUpImg)) {
        std::cerr << "Error: no se pudo crear textura de power-up\n";
    }

    if (m_font.loadFromFile("arial.ttf")) {
        m_fontLoaded = true;
        m_hudText.setFont(m_font);
        m_hudText.setCharacterSize(18);
        m_hudText.setFillColor(sf::Color::White);
        m_hudText.setPosition(10.f, 10.f);

        m_waveText.setFont(m_font);
        m_waveText.setCharacterSize(22);
        m_waveText.setFillColor(sf::Color(255, 255, 100));
        m_waveText.setPosition(280.f, 280.f);

        m_gameOverText.setFont(m_font);
        m_gameOverText.setCharacterSize(36);
        m_gameOverText.setFillColor(sf::Color(255, 80, 80));
        m_gameOverText.setPosition(220.f, 250.f);
    }

	m_player.reset(new Player(m_playerTex, sf::Vector2f(400.f, 520.f)));
    spawnWave();
    m_waveTransitionTimer = 1.5f;
}

void Match::spawnBoss() {
    m_enemies.clear();

    Enemy boss(m_enemyTex, m_bulletTex, sf::Vector2f(400.f, 80.f));
    boss.configureAsBoss(m_level);
    m_enemies.push_back(std::move(boss));
}

void Match::spawnNormalWave(int waveIndex) {
    m_enemies.clear();

    const float baseY = 60.f + waveIndex * 30.f;
    const float speedY = 25.f + m_level * 5.f + waveIndex * 5.f;

    auto addEnemy = [&](float x, float y, Enemy::PatternType pattern,
                        float cooldown, float bulletSpeed, int hp) {
        m_enemies.emplace_back(m_enemyTex, m_bulletTex, sf::Vector2f(x, y));
        Enemy& e = m_enemies.back();
        e.setColor(sf::Color(255, 100, 100));
        e.setRotation(180.f);
        e.setScale(sf::Vector2f(0.8f, 0.8f));
        e.setVelocity(sf::Vector2f(0.f, speedY));
        e.setPattern(pattern);
        e.setShootCooldown(cooldown);
        e.setBulletSpeed(bulletSpeed);
        e.setHP(hp);
        e.setAmplitude(30.f + waveIndex * 10.f);
    };

    switch (waveIndex) {
        case 0:
            for (int i = 0; i < 5; ++i) {
                addEnemy(120.f + i * 140.f, baseY,
                         Enemy::PatternType::Single, 1.8f, 180.f, 1);
            }
            break;
        case 1:
            for (int row = 0; row < 2; ++row) {
                for (int col = 0; col < 4; ++col) {
                    addEnemy(100.f + col * 160.f, baseY + row * 50.f,
                             Enemy::PatternType::Fan, 1.4f, 200.f, 1);
                }
            }
            break;
        default:
            for (int i = 0; i < 3; ++i) {
                addEnemy(200.f + i * 200.f, baseY,
                         Enemy::PatternType::Circular, 2.f, 170.f, 2);
            }
            break;
    }
}

void Match::spawnWave() {
    const bool isBossWave = (m_waveInLevel == WAVES_PER_LEVEL - 1);

    if (isBossWave) {
        spawnBoss();
    } else {
        spawnNormalWave(m_waveInLevel);
    }

    if (m_fontLoaded) {
        std::ostringstream oss;
        if (isBossWave) {
            oss << "JEFE - Nivel " << m_level;
        } else {
            oss << "Oleada " << (m_waveInLevel + 1) << " / " << WAVES_PER_LEVEL
                << "  -  Nivel " << m_level;
        }
        m_waveText.setString(oss.str());
        const sf::FloatRect bounds = m_waveText.getLocalBounds();
        m_waveText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        m_waveText.setPosition(400.f, 300.f);
    }
}

void Match::tryDropPowerUp(const sf::Vector2f& pos, bool guaranteed) {
    std::uniform_real_distribution<float> dist(0.f, 1.f);
    if (!guaranteed && dist(m_rng) > 0.25f) return;

    std::uniform_int_distribution<int> typeDist(0, 3);
    const auto type = static_cast<PowerUp::Type>(typeDist(m_rng));
    m_powerUps.emplace_back(type, m_powerUpTex, pos);
}

void Match::cleanupDead() {
    m_bullets.erase(
        std::remove_if(m_bullets.begin(), m_bullets.end(),
            [](const std::unique_ptr<Bullet>& b) { return !b->isAlive(); }),
        m_bullets.end());

    m_enemies.erase(
        std::remove_if(m_enemies.begin(), m_enemies.end(),
            [](const Enemy& e) { return !e.isAlive(); }),
        m_enemies.end());

    m_powerUps.erase(
        std::remove_if(m_powerUps.begin(), m_powerUps.end(),
            [](const PowerUp& p) { return !p.isAlive(); }),
        m_powerUps.end());
}

void Match::checkCollisions() {
    for (auto& bullet : m_bullets) {
        if (!bullet->isAlive()) continue;

        if (bullet->isFromPlayer()) {
            for (auto& enemy : m_enemies) {
                if (!enemy.isAlive()) continue;
                if (bullet->intersects(enemy)) {
                    enemy.setHP(enemy.getHP() - 1);
                    bullet->destroy();
                    if (enemy.getHP() <= 0) {
                        const sf::Vector2f deathPos = enemy.getPosition();
                        const bool wasBoss = enemy.isBoss();
                        enemy.destroy();
                        m_score += wasBoss ? 1000 : 100;
                        tryDropPowerUp(deathPos, wasBoss);
                    }
                    break;
                }
            }
        } else if (m_player->isAlive() && !m_player->isInvulnerable()
                   && bullet->intersects(*m_player)) {
            m_player->loseLife();
            bullet->destroy();
            if (!m_player->isAlive()) {
                m_gameOver = true;
            }
        }
    }

    if (m_player->isAlive()) {
        for (auto& powerUp : m_powerUps) {
            if (!powerUp.isAlive()) continue;
            if (powerUp.intersects(*m_player)) {
                powerUp.apply(*m_player);
            }
        }
    }
}

void Match::resetMatch() {
    m_score = 0;
    m_level = 1;
    m_waveInLevel = 0;
    m_gameOver = false;
    m_waitingForNextWave = false;
    m_waveTransitionTimer = 0.f;
    m_bullets.clear();
    m_enemies.clear();
    m_powerUps.clear();
	m_player.reset(new Player(m_playerTex, sf::Vector2f(400.f, 520.f)));
    spawnWave();
}

void Match::handleEvent(const sf::Event& event, Game& game) {
    (void)game;
    if (event.type == sf::Event::KeyPressed && m_gameOver
        && event.key.code == sf::Keyboard::R) {
        resetMatch();
    }
}

void Match::update(float dt, Game& game) {
    (void)game;

    if (m_gameOver) return;

    m_player->update(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        for (auto& bullet : m_player->shoot(m_bulletTex)) {
            m_bullets.push_back(std::move(bullet));
        }
    }

    for (auto& enemy : m_enemies) {
        if (!enemy.isAlive()) continue;
        enemy.update(dt);

        if (enemy.getPosition().y > 650.f) {
            enemy.destroy();
            continue;
        }

        for (auto& bullet : enemy.shoot()) {
            m_bullets.push_back(std::move(bullet));
        }
    }

    for (auto& bullet : m_bullets) {
        if (bullet->isAlive()) bullet->update(dt);
    }

    for (auto& powerUp : m_powerUps) {
        if (powerUp.isAlive()) powerUp.update(dt);
    }

    checkCollisions();
    cleanupDead();

    if (m_waveTransitionTimer > 0.f) {
        m_waveTransitionTimer -= dt;
        if (m_waveTransitionTimer <= 0.f) {
            m_waitingForNextWave = false;
            spawnWave();
        }
        return;
    }

    if (m_enemies.empty() && !m_waitingForNextWave) {
        m_waitingForNextWave = true;
        m_waveTransitionTimer = WAVE_DELAY;
        ++m_waveInLevel;

        if (m_waveInLevel >= WAVES_PER_LEVEL) {
            m_waveInLevel = 0;
            ++m_level;
        }
    }
}

void Match::drawHud(sf::RenderWindow& window) {
    if (!m_fontLoaded) return;

    std::ostringstream oss;
    oss << "Puntos: " << m_score
        << "   Vidas: " << m_player->getLives()
        << "   Nivel: " << m_level
        << "   Oleada: " << (m_waveInLevel + 1) << "/" << WAVES_PER_LEVEL;
    m_hudText.setString(oss.str());
    window.draw(m_hudText);

    if (m_waveTransitionTimer > 0.f) {
        window.draw(m_waveText);
    }

    if (m_gameOver) {
        std::ostringstream go;
        go << "GAME OVER\nPuntos: " << m_score << "\n[R] Reintentar";
        m_gameOverText.setString(go.str());
        window.draw(m_gameOverText);
    }
}

void Match::draw(sf::RenderWindow& window) {
    if (m_player->isAlive() || m_gameOver) {
        m_player->draw(window);
    }

    for (const auto& enemy : m_enemies) {
        enemy.draw(window);
    }

    for (const auto& bullet : m_bullets) {
        bullet->draw(window);
    }

    for (const auto& powerUp : m_powerUps) {
        powerUp.draw(window);
    }

    drawHud(window);
}
