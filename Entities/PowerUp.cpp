#include "PowerUp.h"
#include "Player.h"

using namespace sf;

PowerUp::PowerUp(Type type, const Texture& tex, const Vector2f& pos)
    : m_type(type)
{
    setTexture(tex, true);
    setPosition(pos);
    setVelocity(Vector2f(0.f, m_speed));

    switch (type) {
        case Type::ExtraLife:     setColor(Color(255, 80, 80));   break;
        case Type::RapidFire:     setColor(Color(255, 200, 50));  break;
        case Type::SpreadShot:    setColor(Color(80, 200, 255));  break;
        case Type::Shield:        setColor(Color(100, 255, 100)); break;
    }
}

void PowerUp::update(float dt) {
    Entity::update(dt);

    if (getPosition().y > 700.f) {
        destroy();
    }
}

void PowerUp::apply(Player& player) {
    switch (m_type) {
        case Type::ExtraLife:
            player.addLife();
            break;
        case Type::RapidFire:
            player.activateRapidFire(8.f);
            break;
        case Type::SpreadShot:
            player.activateSpreadShot(10.f);
            break;
        case Type::Shield:
            player.activateShield(6.f);
            break;
    }
    destroy();
}
