#include "Match.h"
#include "Game.h"
#include <SFML/Graphics/Image.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <iostream>

Match::Match()
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

    m_player.emplace(m_playerTex, sf::Vector2f(400.f, 520.f));
    spawnWave();
}

void Match::spawnWave() {
    m_enemies.clear();

    for (int i = 0; i < 5; ++i) {
        m_enemies.emplace_back(m_enemyTex, m_bulletTex, sf::Vector2f(150.f + i * 120.f, 80.f));
        Enemy& enemy = m_enemies.back();
        enemy.setColor(sf::Color(255, 100, 100));
        enemy.setVelocity(sf::Vector2f(0.f, 30.f));
        enemy.setPattern(Enemy::PatternType::Fan);
        enemy.setShootCooldown(1.5f);
    }
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
}

void Match::update(float dt, Game& game) {
    (void)game;

    m_player->update(dt);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (auto bullet = m_player->shoot(m_bulletTex)) {
            m_bullets.push_back(std::move(bullet));
        }
    }

    for (auto& enemy : m_enemies) {
        if (!enemy.isAlive()) continue;
        enemy.update(dt);

        for (auto& bullet : enemy.shoot()) {
            m_bullets.push_back(std::move(bullet));
        }
    }

    for (auto& bullet : m_bullets) {
        if (!bullet->isAlive()) continue;
        bullet->update(dt);
    }

    for (auto& bullet : m_bullets) {
        if (!bullet->isAlive()) continue;

        if (bullet->isFromPlayer()) {
            for (auto& enemy : m_enemies) {
                if (!enemy.isAlive()) continue;
                if (bullet->intersects(enemy)) {
                    enemy.setHP(enemy.getHP() - 1);
                    if (enemy.getHP() <= 0) {
                        enemy.destroy();
                        addScore(100);
                    }
                    bullet->destroy();
                    break;
                }
            }
        } else if (m_player->isAlive() && bullet->intersects(*m_player)) {
            m_player->loseLife();
            bullet->destroy();
        }
    }

    cleanupDead();

    if (m_enemies.empty()) {
        spawnWave();
    }
}

void Match::draw(sf::RenderWindow& window) {
    m_player->draw(window);

    for (const auto& enemy : m_enemies) {
        enemy.draw(window);
    }

    for (const auto& bullet : m_bullets) {
        bullet->draw(window);
    }
}
