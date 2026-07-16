#pragma once
#include "Entity.h"

class Player;

class PowerUp : public Entity {
public:
    enum class Type { ExtraLife, RapidFire, SpreadShot, Shield };

    PowerUp(Type type, const sf::Texture& tex, const sf::Vector2f& pos);

    void update(float dt) override;
    void apply(Player& player);

    Type getType() const { return m_type; }

private:
    Type m_type;
    float m_speed = 80.f;
};
