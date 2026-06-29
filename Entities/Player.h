// Player.h
#pragma once
#include "Entity.h"
#include <memory>

class Bullet;

class Player : public Entity {
public:
    Player(const sf::Texture& tex, const sf::Vector2f& pos);
    virtual ~Player() = default;

    void update(float dt) override;

    std::unique_ptr<Bullet> shoot(const sf::Texture& bulletTexture);

    bool canShoot() const { return m_shootTimer <= 0.f; }
    void resetShootTimer() { m_shootTimer = m_shootCooldown; }

    void loseLife() { if (m_lives > 0) --m_lives; }
    int getLives() const { return m_lives; }

private:
    int m_lives = 3;
    float m_speed = 300.f;
    float m_shootCooldown = 0.18f;
    float m_shootTimer = 0.0f;
};