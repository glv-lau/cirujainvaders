#pragma once
#include "Entity.h"

class Bullet : public Entity {
public:
    Bullet(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& vel, bool fromPlayer = false);

    void update(float dt) override;

    bool isFromPlayer() const { return m_fromPlayer; }

private:
    bool m_fromPlayer;
};
