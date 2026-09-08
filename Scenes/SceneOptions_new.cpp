#include "SceneOptions.h"
#include "SceneMenu.h"
#include "../Game.h"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

SceneOptions::SceneOptions()
{
    if (!m_font.loadFromFile("arial.ttf"))
    {
        return;
    }

    m_fontLoaded = true;

    m_title.setFont(m_font);
    m_title.setCharacterSize(48);
    m_title.setString("Opciones");
    m_title.setFillColor(sf::Color::White);
    m_title.setPosition(220.f, 150.f);

    m_masterText.setFont(m_font);
    m_masterText.setCharacterSize(24);
    m_masterText.setFillColor(sf::Color::White);
    m_masterText.setPosition(240.f, 320.f);
    m_masterText.setString("Volumen Master: " + std::to_string(m_masterVolume) + "%");

    m_musicText.setFont(m_font);
    m_musicText.setCharacterSize(24);
    m_musicText.setFillColor(sf::Color::White);
    m_musicText.setPosition(240.f, 360.f);
    m_musicText.setString("Volumen Música: " + std::to_string(m_musicVolume) + "%");

    m_sfxText.setFont(m_font);
    m_sfxText.setCharacterSize(24);
    m_sfxText.setFillColor(sf::Color::White);
    m_sfxText.setPosition(240.f, 400.f);
    m_sfxText.setString("Volumen Efectos: " + std::to_string(m_sfxVolume) + "%");

    m_hudSizeText.setFont(m_font);
    m_hudSizeText.setCharacterSize(24);
    m_hudSizeText.setFillColor(sf::Color::White);
    m_hudSizeText.setPosition(240.f, 440.f);
    m_hudSizeText.setString("Tamaño HUD: " + std::to_string(m_hudSize) + "%");

    m_exitText.setFont(m_font);
    m_exitText.setCharacterSize(24);
    m_exitText.setString("Volver");
    m_exitText.setFillColor(sf::Color::White);
    m_exitText.setPosition(230.f, 480.f);
}

void SceneOptions::handleEvent(const sf::Event& event, Game& game)
{
    if (event.type != sf::Event::KeyPressed) {
        return;
    }

    if (event.key.code == sf::Keyboard::Up) {
        m_selectedOption = (m_selectedOption + 4) % 5;
    } else if (event.key.code == sf::Keyboard::Down) {
        m_selectedOption = (m_selectedOption + 1) % 5;
    } else if (event.key.code == sf::Keyboard::Left) {
        switch (m_selectedOption) {
            case 0:
                m_masterVolume = std::max(0, m_masterVolume - 10);
                game.setmastvolume(m_masterVolume);
                break;
            case 1:
                m_musicVolume = std::max(0, m_musicVolume - 10);
                game.setmusicvolume(m_musicVolume);
                break;
            case 2:
                m_sfxVolume = std::max(0, m_sfxVolume - 10);
                game.setsfxvolume(m_sfxVolume);
                break;
            case 3:
                m_hudSize = std::max(10, m_hudSize - 5);
                game.setHudSize(m_hudSize);
                break;
            default:
                break;
        }
    } else if (event.key.code == sf::Keyboard::Right) {
        switch (m_selectedOption) {
            case 0:
                m_masterVolume = std::min(100, m_masterVolume + 10);
                game.setmastvolume(m_masterVolume);
                break;
            case 1:
                m_musicVolume = std::min(100, m_musicVolume + 10);
                game.setmusicvolume(m_musicVolume);
                break;
            case 2:
                m_sfxVolume = std::min(100, m_sfxVolume + 10);
                game.setsfxvolume(m_sfxVolume);
                break;
            case 3:
                m_hudSize = std::min(100, m_hudSize + 5);
                game.setHudSize(m_hudSize);
                break;
            default:
                break;
        }
    } else if (event.key.code == sf::Keyboard::Return) {
        if (m_selectedOption == 4) {
            game.setScene(new SceneMenu());
        }
    }

    m_masterText.setString("Volumen Master: " + std::to_string(m_masterVolume) + "%");
    m_musicText.setString("Volumen Música: " + std::to_string(m_musicVolume) + "%");
    m_sfxText.setString("Volumen Efectos: " + std::to_string(m_sfxVolume) + "%");
    m_hudSizeText.setString("Tamaño HUD: " + std::to_string(m_hudSize) + "%");
}

void SceneOptions::update(float dt, Game& game)
{
    (void)dt;
    (void)game;

    m_masterText.setFillColor(sf::Color::White);
    m_musicText.setFillColor(sf::Color::White);
    m_sfxText.setFillColor(sf::Color::White);
    m_hudSizeText.setFillColor(sf::Color::White);
    m_exitText.setFillColor(sf::Color::White);

    switch (m_selectedOption) {
        case 0:
            m_masterText.setFillColor(sf::Color::Yellow);
            break;
        case 1:
            m_musicText.setFillColor(sf::Color::Yellow);
            break;
        case 2:
            m_sfxText.setFillColor(sf::Color::Yellow);
            break;
        case 3:
            m_hudSizeText.setFillColor(sf::Color::Yellow);
            break;
        case 4:
            m_exitText.setFillColor(sf::Color::Yellow);
            break;
    }
}

void SceneOptions::draw(sf::RenderWindow &window)
{
    if (!m_fontLoaded)
        return;

    window.draw(m_title);
    window.draw(m_masterText);
    window.draw(m_musicText);
    window.draw(m_sfxText);
    window.draw(m_hudSizeText);
    window.draw(m_exitText);
}
