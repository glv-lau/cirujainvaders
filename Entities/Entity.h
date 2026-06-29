#pragma once
#include <SFML/Graphics.hpp>

/*
 * Entity - clase base para todos los objetos del juego.
 * - update(dt) mueve por m_velocity por defecto (subclases pueden override).
 * - hitbox local configurable (sf::FloatRect: left, top, width, height) en coordenadas locales del sprite.
 * - getGlobalHitbox() devuelve AABB (axis-aligned bounding box) en coordenadas del mundo.
 *
 * IMPORTANTE: no usar 'using namespace' en headers.
 */
class Entity {
public:
    Entity() = default;
    virtual ~Entity() = default;

    virtual void update(float dt);

    virtual void draw(sf::RenderWindow& win);

    virtual sf::FloatRect getBounds() const;

    
    void setHitboxLocal(const sf::FloatRect& localRect); // establecer un rect local personalizado
    void resetHitboxToSprite();                          // resetear hitbox al tamaño del sprite
    sf::FloatRect getHitboxLocal() const;               // devolver hitbox local
    sf::FloatRect getHitboxGlobal() const;              // devolver hitbox transformada a coordenadas globales (AABB)

    // Colisión entre entidades (usa AABB)
    bool intersects(const Entity& other) const;

    // Estado
    bool isAlive() const { return m_alive; }
    void destroy() { m_alive = false; }

    // Visibilidad (dibujo)
    void setVisible(bool v) { m_visible = v; }
    bool isVisible() const { return m_visible; }

    // Position / velocity helpers
    void setPosition(const sf::Vector2f& pos) { m_sprite.setPosition(pos); }
    sf::Vector2f getPosition() const { return m_sprite.getPosition(); }

    void setVelocity(const sf::Vector2f& v) { m_velocity = v; }
    const sf::Vector2f& getVelocity() const { return m_velocity; }

    // Texture / sprite helpers
    void setTexture(const sf::Texture& tex, bool resetOriginToCenter = true);
    void setTextureRect(const sf::IntRect& rect);
    void setOriginCenter(); // centra el origen en localBounds
    void setScale(const sf::Vector2f& s) { m_sprite.setScale(s); }
    void setRotation(float angle) { m_sprite.setRotation(angle); }
    void setColor(const sf::Color& c) { m_sprite.setColor(c); }

protected:
    sf::Sprite m_sprite;
    sf::Vector2f m_velocity{0.f, 0.f};
    bool m_alive = true;
    bool m_visible = true;

    // Hitbox local (por defecto igual a sprite.getLocalBounds())
    sf::FloatRect m_hitboxLocal{0.f, 0.f, 0.f, 0.f};
    bool m_hasCustomHitbox = false; // si false, usamos localBounds del sprite
};