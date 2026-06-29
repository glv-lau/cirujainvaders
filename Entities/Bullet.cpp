#include "Bullet.h"

using namespace sf;

Bullet::Bullet(const Texture& tex, const Vector2f& pos, const Vector2f& vel)
{
    m_sprite.setTexture(tex);
    FloatRect local = m_sprite.getLocalBounds();
    m_sprite.setOrigin(local.width / 2.f, local.height / 2.f);

    m_sprite.setPosition(pos);
    m_velocity = vel;
}

void Bullet::update(float dt) 
{
    Entity::update(dt);

    Vector2f p = m_sprite.getPosition();
    if(p.x < -100.f || p.x > 2000.f || p.y < -100.f || p.y > 2000.f)
    {
        m_alive = false;
    }
}