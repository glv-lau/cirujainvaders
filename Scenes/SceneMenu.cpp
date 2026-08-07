#include "SceneMenu.h"
#include "../Game.h"
#include "../AssetManager.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Keyboard.hpp>

SceneMenu::SceneMenu()
{
    (void)AssetManager::instance().getTexture("menu_bg.png", sf::Color(40, 40, 40), 800, 600);

    if (!m_font.loadFromFile("arial.ttf")) {
        return;
    }

    m_fontLoaded = true;

    m_title.setFont(m_font);
    m_title.setCharacterSize(48);
    m_title.setString("Ciruja Invaders");
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(220.f, 150.f);

    m_startText.setFont(m_font);
    m_startText.setCharacterSize(24);
    m_startText.setString("Presiona Enter para jugar");
    m_startText.setFillColor(sf::Color::White);
    m_startText.setPosition(240.f, 320.f);

    m_exitText.setFont(m_font);
    m_exitText.setCharacterSize(24);
    m_exitText.setString("Presiona Escape para salir");
    m_exitText.setFillColor(sf::Color::White);
    m_exitText.setPosition(230.f, 380.f);
}

void SceneMenu::update(float dt, Game& game) {
    (void)dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
        // TODO: cambiar a Match cuando se integre el menu
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        game.getWindow().close();
    }
}

void SceneMenu::draw(sf::RenderWindow& window) {
    if (!m_fontLoaded) return;

    static sf::RectangleShape background(sf::Vector2f(800.f, 600.f));
    background.setFillColor(sf::Color(35, 35, 45));
    background.setPosition(0.f, 0.f);
    window.draw(background);

    window.draw(m_title);
    window.draw(m_startText);
    window.draw(m_exitText);
}
