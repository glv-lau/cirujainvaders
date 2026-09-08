#include "FormationManager.h"

#include <algorithm>
#include <cmath>

namespace {
    const float kPi = 3.14159265358979323846f;
}

FormationManager::FormationManager()
    : m_pattern(Pattern::SineSweep)
    , m_elapsed(0.f)
    , m_center(400.f, 110.f)
    , m_direction(1.f)
    , m_verticalOffset(0.f)
{
}

void FormationManager::selectPattern(int wave, std::size_t enemyCount) {
    const int choice = (wave + static_cast<int>(enemyCount)) % 9;
    m_pattern = static_cast<Pattern>(choice);
    m_elapsed = 0.f;
    m_center = sf::Vector2f(400.f, 110.f);
    m_direction = (wave % 2 == 0) ? 1.f : -1.f;
    m_verticalOffset = 0.f;
}

void FormationManager::update(std::vector<Enemy>& enemies, float dt,
                              float worldWidth, float worldHeight) {
    m_elapsed += dt;
    if (m_elapsed <= dt * 1.1f) {
        m_center.x = worldWidth * 0.5f;
        m_center.y = worldHeight * 0.16f;
    }
    m_verticalOffset = std::min(worldHeight * 0.22f, m_verticalOffset + 7.f * dt);
    std::size_t count = 0;
    for (const Enemy& enemy : enemies) {
        if (enemy.isAlive() && !enemy.isBoss()) {
            ++count;
        }
    }
    if (count == 0) {
        return;
    }

    const std::size_t columns = std::max<std::size_t>(
        1, static_cast<std::size_t>(std::ceil(std::sqrt(static_cast<float>(count)))));
    const std::size_t rows = (count + columns - 1) / columns;
    float halfWidth = 0.f;
    float halfHeight = 0.f;
    if (m_pattern == Pattern::RotatingCircle || m_pattern == Pattern::ConcentricRings) {
        halfWidth = std::min(worldWidth * 0.38f, std::max(110.f, static_cast<float>(count) * 12.f));
        halfHeight = halfWidth * 0.68f;
    } else if (m_pattern == Pattern::DoubleHelix) {
        halfWidth = std::min(worldWidth * 0.42f, std::max(180.f, static_cast<float>(count) * 14.f));
        halfHeight = std::min(worldHeight * 0.24f, 190.f);
    } else if (m_pattern == Pattern::VFormation) {
        halfWidth = static_cast<float>(count - 1) * 60.f * 0.5f;
        halfHeight = halfWidth * 0.65f + 18.f;
    } else if (m_pattern == Pattern::Lemniscate || m_pattern == Pattern::RadialAccordion) {
        halfWidth = std::min(worldWidth * 0.38f, std::max(120.f, static_cast<float>(columns) * 48.f));
        halfHeight = std::min(worldHeight * 0.25f, std::max(80.f, static_cast<float>(rows) * 42.f));
    } else if (m_pattern == Pattern::DiagonalCross) {
        halfWidth = std::min(worldWidth * 0.35f, 230.f);
        halfHeight = std::min(worldHeight * 0.22f, 210.f);
    } else {
        halfWidth = static_cast<float>(columns - 1) * 60.f * 0.5f;
        halfHeight = static_cast<float>(rows - 1) * 52.f * 0.5f + 24.f;
    }

    const float groupSpeed = 85.f;
    if (m_pattern != Pattern::RotatingCircle && m_pattern != Pattern::ConcentricRings
        && m_pattern != Pattern::DoubleHelix) {
        m_center.x += m_direction * groupSpeed * dt;
    } else {
        m_center.x += m_direction * groupSpeed * 0.75f * dt;
        m_center.y = worldHeight * 0.16f + m_verticalOffset
            + std::sin(m_elapsed * 0.9f) * 45.f;
    }
    const float leftBound = 26.f;
    const float rightBound = std::max(leftBound, worldWidth - 26.f);
    if (m_center.x + halfWidth >= rightBound) {
        m_center.x = rightBound - halfWidth;
        m_direction = -1.f;
    } else if (m_center.x - halfWidth <= leftBound) {
        m_center.x = leftBound + halfWidth;
        m_direction = 1.f;
    }
    if (m_pattern == Pattern::Lemniscate) {
        const float xAmplitude = std::max(0.f, std::min(worldWidth * 0.40f, worldWidth * 0.5f - halfWidth - 26.f));
        const float yAmplitude = std::max(0.f, std::min(95.f, 270.f - halfHeight));
        m_center.x = worldWidth * 0.5f + std::sin(m_elapsed * 0.65f) * xAmplitude;
        m_center.y = worldHeight * 0.20f + m_verticalOffset
            + std::sin(m_elapsed * 1.3f) * yAmplitude;
    } else if (m_pattern == Pattern::DiagonalCross) {
        const float yAmplitude = std::max(0.f, std::min(110.f, 295.f - halfHeight));
        m_center.y = worldHeight * 0.28f + m_verticalOffset
            + std::sin(m_elapsed * 0.55f) * yAmplitude;
    } else if (m_pattern == Pattern::DoubleHelix) {
        m_center.y = worldHeight * 0.18f + m_verticalOffset
            + std::sin(m_elapsed * 0.55f) * 35.f;
    }

    std::size_t formationIndex = 0;
    for (Enemy& enemy : enemies) {
        if (!enemy.isAlive() || enemy.isBoss()) {
            continue;
        }

        const float index = static_cast<float>(formationIndex);
        const float column = static_cast<float>(formationIndex % columns);
        const float row = static_cast<float>(formationIndex / columns);
        ++formationIndex;
        sf::Vector2f offset;
        sf::Vector2f position;
        switch (m_pattern) {
            case Pattern::RotatingCircle: {
                const float angle = m_elapsed * 0.8f + index * 2.f * kPi / static_cast<float>(count);
                offset = sf::Vector2f(std::cos(angle) * halfWidth,
                                      std::sin(angle) * halfHeight);
                break;
            }
            case Pattern::ConcentricRings: {
                const float ring = (formationIndex % 2 == 0) ? 1.f : 0.52f;
                const float direction = (formationIndex % 2 == 0) ? 1.f : -1.f;
                const float angle = direction * m_elapsed * 0.9f
                    + index * 2.f * kPi / static_cast<float>(count);
                offset = sf::Vector2f(std::cos(angle) * halfWidth * ring,
                                      std::sin(angle) * halfHeight * ring);
                break;
            }
            case Pattern::DoubleHelix: {
                const float normalized = (count > 1)
                    ? index / static_cast<float>(count - 1) : 0.5f;
                const float x = (normalized - 0.5f) * 2.f * halfWidth;
                const float phase = (formationIndex % 2 == 0) ? 0.f : kPi;
                offset = sf::Vector2f(x,
                    std::sin(m_elapsed * 1.6f + normalized * 8.f + phase) * halfHeight);
                break;
            }
            case Pattern::OscillatingColumns: {
                const float phase = (column < 1.f) ? 0.f : kPi;
                offset = sf::Vector2f((column - static_cast<float>(columns - 1) * 0.5f) * 60.f,
                                      (row - static_cast<float>(rows - 1) * 0.5f) * 52.f
                                      + std::sin(m_elapsed * 2.f + phase) * 28.f);
                break;
            }
            case Pattern::VFormation: {
                const float vOffset = index - (static_cast<float>(count) - 1.f) * 0.5f;
                const float y = std::abs(vOffset) * 30.f + std::sin(m_elapsed * 1.4f) * 18.f;
                position = sf::Vector2f(m_center.x + vOffset * 48.f, m_center.y + y);
                break;
            }
            case Pattern::SineSweep:
                offset = sf::Vector2f((column - static_cast<float>(columns - 1) * 0.5f) * 60.f,
                                      (row - static_cast<float>(rows - 1) * 0.5f) * 52.f
                                      + std::sin(m_elapsed * 2.1f + index * 0.7f) * 55.f);
                break;
            case Pattern::Lemniscate: {
                const float phase = index * 2.f * kPi / static_cast<float>(count);
                offset = sf::Vector2f(std::sin(phase) * 115.f,
                                      std::sin(phase * 2.f) * 70.f);
                break;
            }
            case Pattern::RadialAccordion: {
                const float scale = 0.65f + 0.35f * (0.5f + 0.5f * std::sin(m_elapsed * 1.7f));
                offset = sf::Vector2f(
                    (column - static_cast<float>(columns - 1) * 0.5f) * 58.f * scale,
                    (row - static_cast<float>(rows - 1) * 0.5f) * 46.f * scale);
                break;
            }
            case Pattern::DiagonalCross: {
                const float normalized = (count > 1)
                    ? index / static_cast<float>(count - 1) : 0.5f;
                const float diagonal = (formationIndex % 2 == 0) ? 1.f : -1.f;
                offset = sf::Vector2f((normalized - 0.5f) * 270.f,
                                      diagonal * (normalized - 0.5f) * 150.f
                                      + (row - static_cast<float>(rows - 1) * 0.5f) * 28.f);
                break;
            }
            default:
                offset = sf::Vector2f((column - static_cast<float>(columns - 1) * 0.5f) * 48.f,
                                      (row - static_cast<float>(rows - 1) * 0.5f) * 42.f
                                      + std::sin(m_elapsed * 2.1f + index * 0.7f) * 55.f);
                break;
        }

        if (m_pattern != Pattern::VFormation) {
            position = m_center + offset;
        }
        enemy.setPosition(position);
        enemy.setVelocity(sf::Vector2f(0.f, 0.f));
    }
}
