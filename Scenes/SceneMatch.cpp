#include "SceneMatch.h"

SceneMatch::SceneMatch() {
    // Acá podés inicializar música de fondo, cargar el mapa, etc.
    if (!m_font.loadFromFile("arial.ttf"))
    {
        return;
    }
    void SceneMenu::onEnter(Game& game) {
        game.playmusic("match_music.ogg", game.getmusicvolume(), true);
    }
    m_fontLoaded = true;

    m_lvltext.setFont(m_font);
    m_lvltext.setCharacterSize(48);
    m_lvltext.setString("Nivel 1");
    m_lvltext.setFillColor(sf::Color::White);
    m_lvltext.setPosition(220.f, 150.f);

    m_puntostext.setFont(m_font);
    m_puntostext.setCharacterSize(24);
    m_puntostext.setString("Puntos: 0");
    m_puntostext.setFillColor(sf::Color::White);
    m_puntostext.setPosition(240.f, 320.f);

    m_vidastext.setFont(m_font);
    m_vidastext.setCharacterSize(24);
    m_vidastext.setString("Vidas: " + std::to_string(m_vidas));
    m_vidastext.setFillColor(sf::Color::White);
    m_vidastext.setPosition(240.f, 350.f);

    m_powerupText.setFont(m_font);
    m_powerupText.setCharacterSize(24);
    m_powerupText.setString("Power-Up: Ninguno");
    m_powerupText.setFillColor(sf::Color::White);
    m_powerupText.setPosition(240.f, 380.f);
}