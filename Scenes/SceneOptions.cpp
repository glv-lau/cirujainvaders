#include "SceneOptions.h"
#include "../Game.h"
#include <SFML/Window/Keyboard.hpp>

SceneOptions::SceneOptions()
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
        return;
    }
    void SceneMenu::onEnter(Game& game) {
        game.playmusic("menu_music.ogg", game.getmusicvolume(), true);
    }

    m_fontLoaded = true;

    m_title.setFont(m_font);
    m_title.setCharacterSize(48);
    m_title.setString("Opciones");
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(220.f, 150.f);

    m_masterText.setFont(m_font);
    m_masterText.setCharacterSize(24);
    m_masterText.setString("Volumen Master");
    m_masterText.setFillColor(sf::Color::White);
    m_masterText.setPosition(240.f, 320.f);

    m_musicText.setFont(m_font);
    m_musicText.setCharacterSize(24);
    m_musicText.setString("Volumen Música");
    m_musicText.setFillColor(sf::Color::White);
    m_musicText.setPosition(240.f, 350.f);

    m_sfxText.setFont(m_font);
    m_sfxText.setCharacterSize(24);
    m_sfxText.setString("Volumen Efectos");
    m_sfxText.setFillColor(sf::Color::White);
    m_sfxText.setPosition(240.f, 380.f);

    m_hudSizeText.setFont(m_font);
    m_hudSizeText.setCharacterSize(24);
    m_hudSizeText.setString("Tamaño HUD");
    m_hudSizeText.setFillColor(sf::Color::White);
    m_hudSizeText.setPosition(240.f, 410.f);

    m_exitText.setFont(m_font);
    m_exitText.setCharacterSize(24);
    m_exitText.setString("Salir");
    m_exitText.setFillColor(sf::Color::White);
    m_exitText.setPosition(230.f, 380.f);
}
void mod_opcion(int valor){
        m_selectedOption += valor;
        if (m_selectedOption < 0) {
            m_selectedOption = 4;
        } else if (m_selectedOption > 4) {
            m_selectedOption = 0;
        }
    }

 void SceneOptions::handleEvent(const sf::Event& event, Game& game)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Up)
        {
            mod_opcion(-1);
        }
        else if (event.key.code == sf::Keyboard::Down)
        {
            mod_opcion(1);
        }
        else if (event.key.code == sf::Keyboard::Enter)
        {
            switch (m_selectedOption)
            {
            case 0:

                while (true) {
                if (event.key.code == sf::Keyboard::Left) {
                    setmastervolume(std::max(0, m_master - 10));
                } else if (event.key.code == sf::Keyboard::Right) {
                    setmastervolume(std::min(100, m_master + 10));
                }else if (event.key.code == sf::Keyboard::escape) {
                    break;
                }
                m_MasterText.setString("Volumen Master: " + std::to_string(m_master) + "%");}   
            case 1:
                while (true) {
                if (event.key.code == sf::Keyboard::Left) {
                    setmusicvolume(std::max(0, m_music - 10));
                } else if (event.key.code == sf::Keyboard::Right) {
                    setmusicvolume(std::min(100, m_music + 10));
                } else if (event.key.code == sf::Keyboard::escape) {
                    break;
                }
                m_MusicText.setString("Volumen Música: " + std::to_string(m_music) + "%");}
            case 2:
                while (true) {
                if (event.key.code == sf::Keyboard::Left) {
                   setsfxvolume(std::max(0, m_sfx - 10));
                } else if (event.key.code == sf::Keyboard::Right) {
                   setsfxvolume(std::min(100, m_sfx + 10));
                } else if (event.key.code == sf::Keyboard::escape) {
                    break;
                }
                m_SFXText.setString("Volumen Efectos: " + std::to_string(m_sfx) + "%");}
            case 3:
                while (true) {
                if (event.key.code == sf::Keyboard::Left) {
                    setHudSize(std::max(10, m_hudSize - 5));
                } else if (event.key.code == sf::Keyboard::Right) {
                    setHudSize(std::min(100, m_hudSize + 5));
                }else if (event.key.code == sf::Keyboard::escape) {
                    break;
                }
                m_HUDSizeText.setString("Tamaño HUD: " + std::to_string(m_hudSize) + "%");} 
            case 4:
                game.setScene(new SceneMenu());
            }
        }
    }
}
void SceneOptions::update(float dt, (void)game)
{
    (void)dt;
    switch (m_selectedOption)
    {
        case 0:
            m_MasterText.setFillColor(sf::Color::Yellow);
            m_MusicText.setFillColor(sf::Color::White);
            m_SFXText.setFillColor(sf::Color::White);
            m_HUDSizeText.setFillColor(sf::Color::White);
            break;
        case 1:
            m_MasterText.setFillColor(sf::Color::White);
            m_MusicText.setFillColor(sf::Color::Yellow);
            m_SFXText.setFillColor(sf::Color::White);
            m_HUDSizeText.setFillColor(sf::Color::White);
            break;
        case 2:
            m_MasterText.setFillColor(sf::Color::White);
            m_MusicText.setFillColor(sf::Color::White);
            m_SFXText.setFillColor(sf::Color::Yellow);
            m_HUDSizeText.setFillColor(sf::Color::White);
            break;
        case 3:
            m_MasterText.setFillColor(sf::Color::White);
            m_MusicText.setFillColor(sf::Color::White);
            m_SFXText.setFillColor(sf::Color::White);
            m_HUDSizeText.setFillColor(sf::Color::Yellow);
            break;
        case 4:
            m_MasterText.setFillColor(sf::Color::White);
            m_MusicText.setFillColor(sf::Color::White);
            m_SFXText.setFillColor(sf::Color::White);
            m_HUDSizeText.setFillColor(sf::Color::White);
            m_exitText.setFillColor(sf::Color::Yellow);
            break;
    }
}

void SceneOptions::draw(sf::RenderWindow &window)
{
    if (!m_fontLoaded)
        return;

    window.draw(m_title);
    window.draw(m_startText);
    window.draw(m_optionsText);
    window.draw(m_exitText);
}