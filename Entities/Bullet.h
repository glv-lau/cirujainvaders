#pragma once
#include "Entity.h"

class Bullet : public Entity {
public:
    enum class PatternType {
        Single,
        Fan,
        Circular,
        Spiral
    };

    Bullet(const sf::Texture& tex, const sf::Vector2f& pos, const sf::Vector2f& vel, bool fromPlayer = false);
    Bullet(const std::string& assetName, const sf::Vector2f& pos, const sf::Vector2f& vel, bool fromPlayer,
           const sf::Color& fallbackColor, unsigned int width, unsigned int height);

    void update(float dt) override;

    bool isFromPlayer() const { return m_fromPlayer; }

private:
    bool m_fromPlayer;
};
