#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <memory>
#include <vector>
#include <cmath>

/*
 * Enemy - enemigo con HP y capacidad de disparar patrones.
 * - update(dt) maneja movimiento básico y timers.
 * - shoot() devuelve vector de unique_ptr<Bullet> con las balas generadas en ese frame.
 *
 * PatternType: circular, fan, spiral.
 */
class Enemy : public Entity {
public:
    using PatternType = Bullet::PatternType;

    Enemy(const sf::Texture& tex, const sf::Texture& bulletTex, const sf::Vector2f& pos);
    Enemy(const std::string& assetName, const sf::Texture& bulletTex, const sf::Vector2f& pos,
          const sf::Color& fallbackColor, unsigned int width, unsigned int height);

    virtual ~Enemy() = default;

    virtual void update(float dt) override;

    // Genera balas si corresponde; devuelve vector (vacío si no dispara)
    std::vector<std::unique_ptr<Bullet>> shoot();

    // Configuración
    void setHP(int hp) { m_hp = hp; }
    int getHP() const { return m_hp; }
    void setShootCooldown(float cd) { m_shootCooldown = cd; }
    void setPattern(PatternType p) { m_pattern = p; }
    void setCircularCount(int c) { m_circularCount = c; }
    void setFanCount(int c) { m_fanCount = c; }
    void setBulletSpeed(float s) { m_bulletSpeed = s; }
    void setSpiralSpeed(float degPerSec) { m_spiralDegPerSec = degPerSec; };
    void setScoreValue(int score) { m_scoreValue = score; }
    int getScoreValue() const { return m_scoreValue; }

    // Simple movement setters
    void setVelocity(const sf::Vector2f& v) { m_velocity = v; }
    void setAmplitude(float a) { m_amplitude = a; }

    void configureAsBoss(int level);
    bool isBoss() const { return m_isBoss; }

private:
    const sf::Texture *m_bulletTexture;

    int m_hp = 1;
    int m_scoreValue = 100;

    // shooting
    float m_shootCooldown = 1.2f;
    float m_shootTimer = 0.f;
    PatternType m_pattern = PatternType::Single;

    // pattern params
    int m_circularCount = 12;
    int m_fanCount = 5;
    float m_bulletSpeed = 200.f;
    float m_spiralDegPerSec = 90.f; // deg per second for spiral
    float m_spiralAngle = 0.f;      // current angle for spiral

    // movement helpers
    float m_timeAlive = 0.f;
    float m_amplitude = 40.f;
    bool m_isBoss = false;
};
