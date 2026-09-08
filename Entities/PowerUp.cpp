#include "PowerUp.h"
#include "Player.h"

using namespace sf;

PowerUp::PowerUp(Type type, const Texture& tex, const Vector2f& pos)
    : m_type(type)
{
    setTextureToSize(tex, 32.f, 32.f, true);
    setHitboxLocal(FloatRect(-24.f, -24.f, 48.f, 48.f));
    setPosition(pos);
    setVelocity(Vector2f(0.f, m_speed));

    switch (type) {
        case Type::ExtraLife:     setColor(Color(182, 255, 255));   break; // B6FFFF
        case Type::RapidFire:     setColor(Color(12, 183, 242));    break; // 0CB7F2
        case Type::SpreadShot:    setColor(Color(9, 121, 176));     break; // 0979B0
        case Type::Shield:        setColor(Color(0, 65, 115));      break; // 004173
    }
}

PowerUp::PowerUp(Type type, const Vector2f& pos)
    : m_type(type)
{
    const std::string assetName = "powerup.png";
    const sf::Color fallbackColor = sf::Color(180, 180, 255);
    setTexture(assetName, fallbackColor, 32, 32, true);
    setHitboxLocal(FloatRect(-24.f, -24.f, 48.f, 48.f));
    setPosition(pos);
    setVelocity(Vector2f(0.f, m_speed));

    switch (type) {
        case Type::ExtraLife:     setColor(Color(182, 255, 255));   break; // B6FFFF
        case Type::RapidFire:     setColor(Color(12, 183, 242));    break; // 0CB7F2
        case Type::SpreadShot:    setColor(Color(9, 121, 176));     break; // 0979B0
        case Type::Shield:        setColor(Color(0, 65, 115));      break; // 004173
    }
}

void PowerUp::update(float dt) {
    Entity::update(dt);

    if (getPosition().y > Entity::getWorldBounds().y + 100.f) {
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
