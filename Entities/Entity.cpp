#include "Entity.h"
#include <algorithm> // for std::max
#include <cmath>

using namespace sf;

void Entity::update(float dt) {
    // Comportamiento por defecto: mover según m_velocity (subclases pueden hacer override y llamar a Entity::update(dt))
    if ((m_velocity.x != 0.f) || (m_velocity.y != 0.f)) {
        m_sprite.move(m_velocity * dt);
    }
}

void Entity::draw(RenderWindow& win) {
    if (m_alive && m_visible) {
        win.draw(m_sprite);
    }
}

FloatRect Entity::getBounds() const {
    return m_sprite.getGlobalBounds();
}

void Entity::setHitboxLocal(const FloatRect& localRect) {
    m_hitboxLocal = localRect;
    m_hasCustomHitbox = true;
}

void Entity::resetHitboxToSprite() {
    // toma las dimensiones locales del sprite (sin transformaciones)
    FloatRect local = m_sprite.getLocalBounds();
    m_hitboxLocal = FloatRect(local.left, local.top, local.width, local.height);
    m_hasCustomHitbox = false; // indicamos que es el hitbox por defecto (pero lo guardamos)
}

FloatRect Entity::getHitboxLocal() const {
    if (m_hasCustomHitbox) return m_hitboxLocal;
    return m_sprite.getLocalBounds();
}

FloatRect Entity::getHitboxGlobal() const {
    // Transformar la hitbox local a coordenadas globales teniendo en cuenta posición y escala.
    // Nota: esta función devuelve una AABB (rectángulo alineado a ejes). No rota la hitbox
    // en caso de rotación del sprite (si rotas, la AABB puede ser más grande que la caja exacta).
    FloatRect local = getHitboxLocal();

    // Obtengo la transformación del sprite (incluye posición, escala, rotación, origin)
    const Transform& t = m_sprite.getTransform();

    // Transformar las cuatro esquinas y calcular AABB
    Vector2f tl = t.transformPoint(local.left, local.top);
    Vector2f tr = t.transformPoint(local.left + local.width, local.top);
    Vector2f bl = t.transformPoint(local.left, local.top + local.height);
    Vector2f br = t.transformPoint(local.left + local.width, local.top + local.height);

    float minX = std::min(std::min(tl.x, tr.x), std::min(bl.x, br.x));
    float maxX = std::max(std::max(tl.x, tr.x), std::max(bl.x, br.x));
    float minY = std::min(std::min(tl.y, tr.y), std::min(bl.y, br.y));
    float maxY = std::max(std::max(tl.y, tr.y), std::max(bl.y, br.y));

    return FloatRect(minX, minY, maxX - minX, maxY - minY);
}

bool Entity::intersects(const Entity& other) const {
    return getHitboxGlobal().intersects(other.getHitboxGlobal());
}

void Entity::setTexture(const Texture& tex, bool resetOriginToCenter) {
    m_sprite.setTexture(tex);
    if (resetOriginToCenter) setOriginCenter();

    // Si la hitbox no fue personalizada, actualizamos el hitbox local al tamaño nuevo
    if (!m_hasCustomHitbox) {
        resetHitboxToSprite();
    }
}

void Entity::setTextureRect(const IntRect& rect) {
    m_sprite.setTextureRect(rect);
    if (!m_hasCustomHitbox) {
        resetHitboxToSprite();
    }
}

void Entity::setOriginCenter() {
    FloatRect b = m_sprite.getLocalBounds();
    m_sprite.setOrigin(b.width / 2.f + b.left, b.height / 2.f + b.top);
    // si no hay hitbox personalizada, actualizamos la hitbox default
    if (!m_hasCustomHitbox) resetHitboxToSprite();
}