#include "Enemy.h"
#include "Bullet.h"
#include <SFML/System/Vector2.hpp>
#include <cmath>

using namespace sf;

static constexpr float PI_F = 3.14159265358979323846f;

Enemy::Enemy(const Texture& tex, const Texture& bulletTex, const Vector2f& pos)
    : m_bulletTexture(bulletTex)
{
    setTexture(tex, true);
    setPosition(pos);
}

void Enemy::update(float dt) {
    // ejemplo: movimiento vertical por velocity + sin en x según m_timeAlive
    m_timeAlive += dt;
    // movimiento base
    if ((m_velocity.x != 0.f) || (m_velocity.y != 0.f)) {
        m_sprite.move(m_velocity * dt);
    }

    // añadir oscilación horizontal leve
    Vector2f p = getPosition();
    p.x += std::sin(m_timeAlive * 2.0f) * (m_amplitude * dt); // pequeño ajuste por frame
    setPosition(p);

    // timers
    if (m_shootTimer > 0.f) m_shootTimer -= dt;

    // para spiral, actualizar ángulo
    if (m_pattern == PatternType::Spiral) {
        m_spiralAngle += m_spiralDegPerSec * dt; // grados
        // mantener 0..360
        if (m_spiralAngle >= 360.f) m_spiralAngle -= 360.f;
    }
}

std::vector<std::unique_ptr<Bullet>> Enemy::shoot() {
    std::vector<std::unique_ptr<Bullet>> out;
    if (m_shootTimer > 0.f) return out;

    Vector2f pos = getPosition();

    switch (m_pattern) {
        case PatternType::Single: {
            // disparo simple hacia abajo
            Vector2f vel(0.f, m_bulletSpeed);
            out.push_back(std::make_unique<Bullet>(m_bulletTexture, pos, vel));
            break;
        }
        case PatternType::Fan: {
            // abanico hacia abajo: centered at 90deg (down)
            float centerDeg = 90.f;
            float spread = 60.f; // grados totales
            int n = std::max(1, m_fanCount);
            for (int i = 0; i < n; ++i) {
                float angle = centerDeg - spread/2.f + (spread * i) / (n - 1.0f);
                float r = angle * PI_F / 180.f;
                Vector2f vel(std::cos(r) * m_bulletSpeed, std::sin(r) * m_bulletSpeed);
                out.push_back(std::make_unique<Bullet>(m_bulletTexture, pos, vel));
            }
            break;
        }
        case PatternType::Circular: {
            int n = std::max(1, m_circularCount);
            for (int i = 0; i < n; ++i) {
                float angle = (360.f * i) / n;
                float r = angle * PI_F / 180.f;
                Vector2f vel(std::cos(r) * m_bulletSpeed, std::sin(r) * m_bulletSpeed);
                out.push_back(std::make_unique<Bullet>(m_bulletTexture, pos, vel));
            }
            break;
        }
        case PatternType::Spiral: {
            // crea una o pocas balas con ángulo dependiente de m_spiralAngle
            // puede crear más de una por disparo si querés
            float angle = m_spiralAngle;
            float r = angle * PI_F / 180.f;
            Vector2f vel(std::cos(r) * m_bulletSpeed, std::sin(r) * m_bulletSpeed);
            out.push_back(std::make_unique<Bullet>(m_bulletTexture, pos, vel));
            // opcional: una segunda bala con offset
            float r2 = (angle + 20.f) * PI_F / 180.f;
            Vector2f vel2(std::cos(r2) * m_bulletSpeed, std::sin(r2) * m_bulletSpeed);
            out.push_back(std::make_unique<Bullet>(m_bulletTexture, pos, vel2));
            break;
        }
    }

    // resetear timer
    m_shootTimer = m_shootCooldown;
    return out;
}