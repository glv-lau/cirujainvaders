#ifndef SCENEMATCH_H
#define SCENEMATCH_H

#include "Scene.h"
#include "Match.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class SceneMatch : public Scene {
public:
    SceneMatch();
    ~SceneMatch() override = default;

    void update(float dt, Game& game) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event, Game& game) override;

private:
    sf::Font m_font;
    sf::Text m_lvltext;
    sf::Text m_puntostext;
    sf::Text m_vidastext;
    int m_vidas = 3;
    sf::Text m_powerupText;
    int m_corazones = 3;
    Match m_match;
    bool m_fontLoaded = false;
};