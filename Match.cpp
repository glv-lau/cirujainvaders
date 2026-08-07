#include "Match.h"
#include "Game.h"
#include "AssetManager.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>

Match::Match()
    : m_rng(std::random_device{}())
{
    m_playerTex = AssetManager::instance().getTexture("player.png", sf::Color(80, 180, 255), 48, 48);
    m_enemyEasyTex = AssetManager::instance().getTexture("enemy_basic.png", sf::Color(255, 120, 120), 40, 40);
    m_enemyHardTex = AssetManager::instance().getTexture("enemy_hard.png", sf::Color(220, 80, 220), 42, 42);
    m_enemySpecialTex = AssetManager::instance().getTexture("enemy_special.png", sf::Color(255, 220, 80), 44, 44);
    m_enemyBossTex = AssetManager::instance().getTexture("enemy_boss.png", sf::Color(180, 50, 255), 72, 72);
    m_bulletTex = AssetManager::instance().getTexture("bullet_player.png", sf::Color(255, 255, 80), 6, 6);
    m_powerUpTex = AssetManager::instance().getTexture("powerup.png", sf::Color(180, 180, 255), 14, 14);

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
    m_waveEnemyCount = 1;

    Enemy boss(m_enemyBossTex, m_bulletTex, sf::Vector2f(400.f, 80.f));
    boss.configureAsBoss(m_level);
    boss.setScoreValue(1200 + m_level * 80);
    m_enemies.push_back(std::move(boss));
}

void Match::spawnNormalWave(int waveIndex) {
    m_enemies.clear();

    const float baseY = 60.f + waveIndex * 45.f;
    const float speedY = 18.f + m_level * 6.f + waveIndex * 3.f;
    const int minCount = 4 + waveIndex * 3 + (m_level - 1) * 2;
    const int maxCount = minCount + 4 + waveIndex + (m_level - 1);
    const int enemyCount = (waveIndex == WAVES_PER_LEVEL - 2)
        ? maxCount
        : std::uniform_int_distribution<int>(minCount, maxCount)(m_rng);
    m_waveEnemyCount = enemyCount;
    m_highestNormalWaveCount = std::max(m_highestNormalWaveCount, enemyCount);

    std::uniform_int_distribution<int> typeRoll(0, 99);
    std::uniform_real_distribution<float> xDist(80.f, 720.f);

    auto addEnemy = [&](float x, float y, const sf::Texture& tex, Enemy::PatternType pattern,
                        float cooldown, float bulletSpeed, int hp, int scoreValue,
                        const sf::Color& color, int fanCount = 5, int circularCount = 12) {
        m_enemies.emplace_back(tex, m_bulletTex, sf::Vector2f(x, y));
        Enemy& e = m_enemies.back();
        e.setColor(color);
        e.setRotation(180.f);
        e.setScale(sf::Vector2f(0.85f, 0.85f));
        e.setVelocity(sf::Vector2f(0.f, speedY));
        e.setPattern(pattern);
        e.setShootCooldown(cooldown);
        e.setBulletSpeed(bulletSpeed);
        e.setHP(hp);
        e.setScoreValue(scoreValue);
        e.setAmplitude(24.f + waveIndex * 8.f);
        e.setFanCount(fanCount);
        e.setCircularCount(circularCount);
    };

    for (int i = 0; i < enemyCount; ++i) {
        float x = xDist(m_rng);
        float y = baseY + (i / 8) * 40.f;
        int roll = typeRoll(m_rng);

        if (waveIndex == 0) {
            if (roll < 70) {
                addEnemy(x, y, m_enemyEasyTex, Enemy::PatternType::Single, 2.0f, 160.f, 1, 100,
                         sf::Color(255, 180, 180), 4, 10);
            } else {
                addEnemy(x, y, m_enemyHardTex, Enemy::PatternType::Fan, 1.8f, 180.f, 2, 180,
                         sf::Color(255, 160, 255), 5, 10);
            }
        } else if (waveIndex == 1) {
            if (roll < 45) {
                addEnemy(x, y, m_enemyEasyTex, Enemy::PatternType::Single, 1.8f, 170.f, 1, 120,
                         sf::Color(255, 170, 170), 4, 10);
            } else if (roll < 80) {
                addEnemy(x, y, m_enemyHardTex, Enemy::PatternType::Fan, 1.5f, 190.f, 3, 240,
                         sf::Color(220, 160, 255), 6, 12);
            } else {
                const Enemy::PatternType specialPattern = (typeRoll(m_rng) % 2 == 0)
                    ? Enemy::PatternType::Circular
                    : Enemy::PatternType::Spiral;
                addEnemy(x, y, m_enemySpecialTex, specialPattern, 1.6f, 180.f, 2, 300,
                         sf::Color(255, 210, 120), 5, 12);
            }
        } else {
            if (roll < 30) {
                addEnemy(x, y, m_enemyEasyTex, Enemy::PatternType::Single, 1.7f, 170.f, 1, 140,
                         sf::Color(255, 150, 150), 4, 10);
            } else if (roll < 70) {
                addEnemy(x, y, m_enemyHardTex, Enemy::PatternType::Fan, 1.4f, 200.f, 3, 280,
                         sf::Color(220, 140, 255), 7, 14);
            } else {
                const Enemy::PatternType specialPattern = (typeRoll(m_rng) % 3 == 0)
                    ? Enemy::PatternType::Circular
                    : Enemy::PatternType::Spiral;
                addEnemy(x, y, m_enemySpecialTex, specialPattern, 1.3f, 210.f, 2, 340,
                         sf::Color(255, 220, 130), 8, 14);
            }
        }
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
                << "  -  Nivel " << m_level
                << "  -  Enemigos: " << m_waveEnemyCount;
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
                        const int enemyScore = enemy.getScoreValue();
                        enemy.destroy();
                        m_score += enemyScore;
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
    m_waveEnemyCount = 0;
    m_highestNormalWaveCount = 0;
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
        << "   Oleada: " << (m_waveInLevel + 1) << "/" << WAVES_PER_LEVEL
        << "   Enemigos: " << m_waveEnemyCount;
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
