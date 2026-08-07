#include "Bullet.h"

using namespace sf;

Bullet::Bullet(const Texture& tex, const Vector2f& pos, const Vector2f& vel, bool fromPlayer)
    : m_fromPlayer(fromPlayer)
{
    setTexture(tex, true);
    setPosition(pos);
    setVelocity(vel);
}

Bullet::Bullet(const std::string& assetName, const Vector2f& pos, const Vector2f& vel, bool fromPlayer,
               const Color& fallbackColor, unsigned int width, unsigned int height)
    : m_fromPlayer(fromPlayer)
{
    setTexture(assetName, fallbackColor, width, height, true);
    setPosition(pos);
    setVelocity(vel);
}

void Bullet::update(float dt) {
    Entity::update(dt);

    const Vector2f p = getPosition();
    if (p.x < -100.f || p.x > 900.f || p.y < -100.f || p.y > 700.f) {
        destroy();
    }
}
