#include "Enemy.h"
#include "Bullet.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

using namespace sf;

static constexpr float PI_F = 3.14159265358979323846f;

Enemy::Enemy(const Texture& tex, const Texture& bulletTex, const Vector2f& pos)
    : m_bulletTexture(&bulletTex)
{
    setTexture(tex, true);
    setPosition(pos);
}

Enemy::Enemy(const std::string& assetName, const Texture& bulletTex, const Vector2f& pos, const Color& fallbackColor, unsigned int width, unsigned int height)
    : m_bulletTexture(&bulletTex)
{
    setTexture(assetName, fallbackColor, width, height, true);
    setPosition(pos);
}

void Enemy::update(float dt) {
    m_timeAlive += dt;

    if (m_hasTarget) {
        const Vector2f dir = m_targetPosition - getPosition();
        const float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (length > 0.0001f) {
            float speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
            if (speed < 1.f) {
                speed = 85.f;
            }
            const Vector2f normDir = dir / length;
            m_velocity = normDir * speed;
        }
    }

    if ((m_velocity.x != 0.f) || (m_velocity.y != 0.f)) {
        m_sprite.move(m_velocity * dt);
    }

    Vector2f p = getPosition();
    p.x = std::max(26.f, std::min(774.f, p.x));
    p.y = std::max(30.f, std::min(570.f, p.y));
    setPosition(p);

    if (m_shootTimer > 0.f) m_shootTimer -= dt;

    if (m_pattern == PatternType::Spiral) {
        m_spiralAngle += m_spiralDegPerSec * dt;
        if (m_spiralAngle >= 360.f) m_spiralAngle -= 360.f;
    }
}

std::vector<std::unique_ptr<Bullet>> Enemy::shoot() {
    std::vector<std::unique_ptr<Bullet>> out;
    if (m_shootTimer > 0.f) return out;

    Vector2f pos = getPosition();
    Vector2f aimDir(0.f, 1.f);
    if (m_hasTarget) {
        Vector2f delta = m_targetPosition - pos;
        float len = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        if (len > 0.0001f) {
            aimDir = delta / len;
        }
    }

    if (m_isBoss) {
        const int starCount = 12;
        const float baseAngle = m_spiralAngle;
        for (int i = 0; i < starCount; ++i) {
            const float angle = (360.f * i) / starCount + baseAngle;
            const float r = angle * PI_F / 180.f;
            const Vector2f vel(std::cos(r) * m_bulletSpeed, std::sin(r) * m_bulletSpeed);
            out.push_back(std::make_unique<Bullet>(*m_bulletTexture, pos, vel));
        }

        for (int i = 0; i < 6; ++i) {
            const float angle = (360.f * i) / 6.f + baseAngle * 1.7f;
            const float r = angle * PI_F / 180.f;
            const Vector2f vel(std::cos(r) * (m_bulletSpeed * 0.8f), std::sin(r) * (m_bulletSpeed * 0.8f));
            out.push_back(std::make_unique<Bullet>(*m_bulletTexture, pos, vel));
        }

        m_spiralAngle += 38.f;
    } else {
        switch (m_pattern) {
            case PatternType::Single: {
                Vector2f vel(aimDir.x * m_bulletSpeed, aimDir.y * m_bulletSpeed);
                out.push_back(std::make_unique<Bullet>(*m_bulletTexture, pos, vel));
                break;
            }
            case PatternType::Fan: {
                float centerDeg = 90.f;
                if (m_hasTarget) {
                    centerDeg = std::atan2(aimDir.y, aimDir.x) * 180.f / PI_F + 90.f;
                }
                float spread = 60.f;
                int n = std::max(1, m_fanCount);
                for (int i = 0; i < n; ++i) {
                    const float step = (n > 1) ? (spread * i) / (n - 1.0f) : 0.f;
                    float angle = centerDeg - spread / 2.f + step;
                    float r = angle * PI_F / 180.f;
                    Vector2f vel(std::cos(r) * m_bulletSpeed, std::sin(r) * m_bulletSpeed);
                    out.push_back(std::make_unique<Bullet>(*m_bulletTexture, pos, vel));
                }
                break;
            }
            case PatternType::Circular: {
                int n = std::max(1, m_circularCount);
                for (int i = 0; i < n; ++i) {
                    float angle = (360.f * i) / n;
                    float r = angle * PI_F / 180.f;
                    Vector2f vel(std::cos(r) * m_bulletSpeed, std::sin(r) * m_bulletSpeed);
                    out.push_back(std::make_unique<Bullet>(*m_bulletTexture, pos, vel));
                }
                break;
            }
            case PatternType::Spiral: {
                float angle = m_spiralAngle;
                float r = angle * PI_F / 180.f;
                Vector2f vel(std::cos(r) * m_bulletSpeed, std::sin(r) * m_bulletSpeed);
                out.push_back(std::make_unique<Bullet>(*m_bulletTexture, pos, vel));
                float r2 = (angle + 20.f) * PI_F / 180.f;
                Vector2f vel2(std::cos(r2) * m_bulletSpeed, std::sin(r2) * m_bulletSpeed);
                out.push_back(std::make_unique<Bullet>(*m_bulletTexture, pos, vel2));
                break;
            }
        }
    }

    m_shootTimer = m_shootCooldown;
    return out;
}

void Enemy::configureAsBoss(int level) {
    m_isBoss = true;
    m_hp = 45 + level * 18;
    setScale(Vector2f(2.2f, 2.2f));
    setColor(Color(124, 14, 54));
    setRotation(180.f);
    setPattern(PatternType::Spiral);
    setShootCooldown(0.28f);
    setBulletSpeed(200.f + level * 25.f);
    setSpiralSpeed(190.f);
    setVelocity(Vector2f(80.f, 20.f));
    setAmplitude(80.f);
}
