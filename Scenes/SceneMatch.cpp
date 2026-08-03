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
    void SceneMatch::update(float dt, Game& game) {
        m_match.update(game);
        m_puntostext.setString("Puntos: " + std::to_string(m_match.get_score()));
        m_vidastext.setString("Vidas: " + std::to_string(m_vidas));
        m_player.update();
       for (Bullet& bullet : m_bullets) {bullet.update(dt);}
        
    }
    void SceneMatch::draw(sf::RenderWindow& window) {
        window.clear();
        m_match.draw(window);
        window.draw(m_lvltext);
        window.draw(m_puntostext);
        window.draw(m_vidastext);
        window.draw(m_powerupText);
        m_player.draw(window);
        bullet.draw(window);
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