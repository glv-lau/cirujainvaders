#include "SceneStageIntro.h"
#include "../Game.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <string>

namespace {
    bool loadFontFallback(sf::Font& font) {
        const std::string candidates[] = {
            "arial.ttf",
            "C:/Windows/Fonts/arial.ttf",
            "C:/Windows/Fonts/calibri.ttf",
            "C:/Windows/Fonts/consola.ttf",
            "C:/Program Files (x86)/ZinjaI/MinGW32-gcc6/arial.ttf",
            "C:/Users/Lau/Documents/GitHub/cirujainvaders/arial.ttf"
        };

        for (size_t i = 0; i < sizeof(candidates) / sizeof(candidates[0]); ++i) {
            if (font.loadFromFile(candidates[i])) {
                return true;
            }
        }
        return false;
    }
}

SceneStageIntro::SceneStageIntro(int stage, float duration)
    : m_stage(stage), m_timer(duration)
{
    if (!loadFontFallback(m_font)) {
        return;
    }
    m_fontLoaded = true;

    m_text.setFont(m_font);
    m_text.setCharacterSize(48);
    m_text.setString("STAGE " + std::to_string(m_stage) + ", GO!!");
    m_text.setFillColor(sf::Color::White);
    const sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    m_text.setPosition(400.f, 300.f);
}

void SceneStageIntro::handleEvent(const sf::Event& event, Game& game) {
    if (event.type == sf::Event::KeyPressed) {
        game.setScene(new SceneMatch());
    }
}

void SceneStageIntro::update(float dt, Game& game) {
    (void)game;
    m_timer -= dt;
    if (m_timer <= 0.f) {
        game.setScene(new SceneMatch());
    }
}

void SceneStageIntro::draw(sf::RenderWindow& window) {
    static sf::RectangleShape background(sf::Vector2f(800.f, 600.f));
    background.setFillColor(sf::Color(15, 15, 20));
    background.setPosition(0.f, 0.f);
    window.draw(background);

    if (m_fontLoaded) {
        window.draw(m_text);
    }
}
