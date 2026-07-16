#include "SceneMenu.h"
#include "Game.h"
#include <SFML/Window/Keyboard.hpp>

SceneMenu::SceneMenu()
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
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

void SceneMenu::update(float dt, Game &game)
{
    (void)dt;

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::up)
        {
            mod_opcion(-1);
        }
        if (event.key.code == sf::Keyboard::down)
        {
            mod_opcion(1);
        }
    }
    if (event.key.code == sf::Keyboard::Enter)
    {

        switch (getSelectedOption())
        {
        case 0:
            // Iniciar juego
            break;

        case 1:
            // Abrir opciones
            break;

        case 2:
            game.getWindow().close();
            break;
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        game.getWindow().close();
    }
}

void SceneMenu::draw(sf::RenderWindow &window)
{
    if (!m_fontLoaded)
        return;

    window.draw(m_title);
    window.draw(m_startText);
    window.draw(m_exitText);
}
