#include "SceneMenu.h"
#include "../Game.h"
#include "../AssetManager.h"
#include "SceneStageIntro.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>

namespace {
    const sf::Color kMenuNormal = sf::Color(182, 255, 255);
    const sf::Color kMenuSelected = sf::Color(12, 183, 242);
    const sf::Color kMenuTitle = sf::Color::White;

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

SceneMenu::SceneMenu()
{
    (void)AssetManager::instance().getTexture("menu_bg.png", sf::Color(40, 40, 40), 800, 600);

    if (!loadFontFallback(m_font)) {
        return;
    }

    m_fontLoaded = true;

    m_title.setFont(m_font);
    m_title.setCharacterSize(48);
    m_title.setString("CIRUJAINVADERS");
    m_title.setFillColor(kMenuTitle);
    m_title.setPosition(160.f, 120.f);

    m_startText.setFont(m_font);
    m_startText.setCharacterSize(30);
    m_startText.setString("START");
    m_startText.setFillColor(kMenuNormal);
    m_startText.setPosition(330.f, 260.f);

    m_optionsText.setFont(m_font);
    m_optionsText.setCharacterSize(30);
    m_optionsText.setString("OPTIONS");
    m_optionsText.setFillColor(kMenuNormal);
    m_optionsText.setPosition(300.f, 320.f);

    m_exitText.setFont(m_font);
    m_exitText.setCharacterSize(30);
    m_exitText.setString("EXIT");
    m_exitText.setFillColor(kMenuNormal);
    m_exitText.setPosition(335.f, 380.f);

    updateSelectionColors();
}

void SceneMenu::activateSelection(Game& game) {
    switch (m_selectedOption) {
        case 0:
            game.setScene(new SceneStageIntro());
            break;
        case 1:
            break;
        case 2:
            game.getWindow().close();
            break;
        default:
            break;
    }
}

void SceneMenu::updateSelectionColors() {
    m_startText.setFillColor(m_selectedOption == 0 ? kMenuSelected : kMenuNormal);
    m_optionsText.setFillColor(m_selectedOption == 1 ? kMenuSelected : kMenuNormal);
    m_exitText.setFillColor(m_selectedOption == 2 ? kMenuSelected : kMenuNormal);
}

void SceneMenu::handleEvent(const sf::Event& event, Game& game) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
            m_selectedOption = (m_selectedOption + 2) % 3;
        } else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
            m_selectedOption = (m_selectedOption + 1) % 3;
        } else if (event.key.code == sf::Keyboard::Return || event.key.code == sf::Keyboard::Space) {
            activateSelection(game);
        } else if (event.key.code == sf::Keyboard::Escape) {
            game.getWindow().close();
        }
        updateSelectionColors();
    }

    if (event.type == sf::Event::MouseMoved) {
        const sf::Vector2f pos(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
        if (m_startText.getGlobalBounds().contains(pos)) {
            m_selectedOption = 0;
        } else if (m_optionsText.getGlobalBounds().contains(pos)) {
            m_selectedOption = 1;
        } else if (m_exitText.getGlobalBounds().contains(pos)) {
            m_selectedOption = 2;
        }
        updateSelectionColors();
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f pos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
        if (m_startText.getGlobalBounds().contains(pos)) {
            m_selectedOption = 0;
            activateSelection(game);
        } else if (m_optionsText.getGlobalBounds().contains(pos)) {
            m_selectedOption = 1;
            updateSelectionColors();
        } else if (m_exitText.getGlobalBounds().contains(pos)) {
            m_selectedOption = 2;
            activateSelection(game);
        }
    }
}

void SceneMenu::update(float dt, Game& game) {
    (void)dt;
    (void)game;
}

void SceneMenu::draw(sf::RenderWindow& window) {
    if (!m_fontLoaded) return;

    static sf::RectangleShape background(sf::Vector2f(800.f, 600.f));
    background.setFillColor(sf::Color(5, 12, 22));
    background.setPosition(0.f, 0.f);
    window.draw(background);

    window.draw(m_title);
    window.draw(m_startText);
    window.draw(m_optionsText);
    window.draw(m_exitText);
}
