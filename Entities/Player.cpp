#include "Player.h"
#include "Bullet.h"
#include <algorithm>
#include <cmath>

using namespace sf;

Player::Player(const Texture& tex, const Vector2f& pos) {
    setTexture(tex);
    setPosition(pos);
    setRotation(0.f);
}

float Player::getEffectiveCooldown() const {
    return (m_rapidFireTimer > 0.f) ? 0.08f : m_shootCooldown;
}

void Player::update(float dt) {
    if (m_invulnTimer > 0.f) m_invulnTimer -= dt;
    if (m_rapidFireTimer > 0.f) m_rapidFireTimer -= dt;
    if (m_spreadShotTimer > 0.f) m_spreadShotTimer -= dt;
    if (m_shieldTimer > 0.f) m_shieldTimer -= dt;

    m_blinkTimer += dt;

    Vector2f move{0.f, 0.f};
    if (Keyboard::isKeyPressed(Keyboard::Left))  move.x -= m_speed;
    if (Keyboard::isKeyPressed(Keyboard::Right)) move.x += m_speed;
    if (Keyboard::isKeyPressed(Keyboard::Up))    move.y -= m_speed;
    if (Keyboard::isKeyPressed(Keyboard::Down))  move.y += m_speed;

    setVelocity(move);
    Entity::update(dt);

    Vector2f pos = getPosition();
    const float margin = 20.f;
    pos.x = std::max(margin, std::min(800.f - margin, pos.x));
    pos.y = std::max(400.f, std::min(580.f, pos.y));
    setPosition(pos);

    if (m_shootTimer > 0.f) m_shootTimer -= dt;
}

void Player::draw(RenderWindow& win) const {
    if (!isAlive()) return;

    if (isInvulnerable() && std::fmod(m_blinkTimer, 0.15f) < 0.075f) {
        return;
    }

    Entity::draw(win);
}

std::vector<std::unique_ptr<Bullet>> Player::shoot(const Texture& bulletTexture) {
    std::vector<std::unique_ptr<Bullet>> bullets;
    if (!canShoot() || !isAlive()) return bullets;

    Vector2f pos = getPosition();
    const float offset = m_sprite.getLocalBounds().height / 2.f + 6.f;
    const Vector2f basePos = pos + Vector2f(0.f, -offset);
    const float speed = 700.f;

    if (m_spreadShotTimer > 0.f) {
        const float angles[] = {-20.f, 0.f, 20.f};
        for (float deg : angles) {
            const float rad = deg * 3.14159265f / 180.f;
            Vector2f vel(std::sin(rad) * speed, -std::cos(rad) * speed);
            bullets.push_back(std::make_unique<Bullet>(bulletTexture, basePos, vel, true));
        }
    } else {
        bullets.push_back(std::make_unique<Bullet>(
            bulletTexture, basePos, Vector2f(0.f, -speed), true));
    }

    resetShootTimer();
    return bullets;
}

void Player::loseLife() {
    if (isInvulnerable() || !isAlive()) return;

    if (hasShield()) {
        m_shieldTimer = 0.f;
        m_invulnTimer = m_invulnDuration;
        return;
    }

    --m_lives;
    if (m_lives <= 0) {
        destroy();
    } else {
        m_invulnTimer = m_invulnDuration;
    }
}

void Player::addLife() {
    if (m_lives < 5) ++m_lives;
}

void Player::activateRapidFire(float duration) {
    m_rapidFireTimer = duration;
}

void Player::activateSpreadShot(float duration) {
    m_spreadShotTimer = duration;
}

void Player::activateShield(float duration) {
    m_shieldTimer = duration;
}
