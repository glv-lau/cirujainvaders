#ifndef MATCH_H
#define MATCH_H

#include "Scenes/Scene.h"
#include "Entities/Player.h"
#include "Entities/Enemy.h"
#include "Entities/Bullet.h"
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <optional>
#include <vector>

class Match : public Scene {
public:
    Match();
    ~Match() override = default;

    void update(float dt, Game& game) override;
    void draw(sf::RenderWindow& window) override;

    void addScore(int points) { m_score += points; }
    int getScore() const { return m_score; }

private:
    sf::Texture m_playerTex;
    sf::Texture m_enemyTex;
    sf::Texture m_bulletTex;

    std::optional<Player> m_player;
    std::vector<Enemy> m_enemies;
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    int m_score = 0;

    void spawnWave();
    void cleanupDead();
};

#endif
