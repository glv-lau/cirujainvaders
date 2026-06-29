// Player.cpp
#include "Player.h"
#include "Bullet.h"

using namespace sf;

Player::Player(const sf::Texture& tex, const sf::Vector2f& pos) {
    setTexture(tex);
    setPosition(pos);
}

void Player::update(float dt) {
    Vector2f move{0.f, 0.f};
    if (Keyboard::isKeyPressed(Keyboard::Left))  move.x -= m_speed;
    if (Keyboard::isKeyPressed(Keyboard::Right)) move.x += m_speed;
    if (Keyboard::isKeyPressed(Keyboard::Up))    move.y -= m_speed;
    if (Keyboard::isKeyPressed(Keyboard::Down))  move.y += m_speed;

    setVelocity(move);
    Entity::update(dt);

    if (m_shootTimer > 0.f) m_shootTimer -= dt;
}

std::unique_ptr<Bullet> Player::shoot(const sf::Texture& bulletTexture) {
    if (!canShoot()) return nullptr;

    Vector2f pos = getPosition();
    float offset = m_sprite.getLocalBounds().height / 2.f + 6.f;
    Vector2f bulletPos = pos + Vector2f(0.f, -offset);

    Vector2f bulletVel{0.f, -700.f};

    auto b = std::make_unique<Bullet>(bulletTexture, bulletPos, bulletVel);
    resetShootTimer();
    return b;
}