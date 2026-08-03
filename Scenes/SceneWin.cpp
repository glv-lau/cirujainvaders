#include "SceneWin.h"
#include "../Game.h"
#include <SFML/Window/Keyboard.hpp>
SceneWin::SceneWin()
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
        return;
    }

    m_fontLoaded = true;

    m_ganasteText.setFont(m_font);
    m_ganasteText.setCharacterSize(48);
    m_ganasteText.setString("¡Ganaste!");
    m_ganasteText.setFillColor(sf::Color::White);
    m_ganasteText.setPosition(220.f, 150.f);

    m_puntostext.setFont(m_font);
    m_puntostext.setCharacterSize(24);
    m_puntostext.setString("Puntos: " + std::to_string(m_match.get_score()));
    m_puntostext.setFillColor(sf::Color::White);
    m_puntostext.setPosition(240.f, 320.f);

    m_enterreiniciarText.setFont(m_font);
    m_enterreiniciarText.setCharacterSize(24);
    m_enterreiniciarText.setString("Presiona Enter para reiniciar");
    m_enterreiniciarText.setFillColor(sf::Color::White);
    m_enterreiniciarText.setPosition(240.f, 350.f);

    SceneWin::handleEvent(const sf::Event& event, Game& game)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Enter)
            {
                game.changeScene(new SceneMenu());
            }
        }
    }

}