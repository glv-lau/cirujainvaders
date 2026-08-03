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
    sf::Text m_puntostext;
    sf::Text m_ganasteText;
    sf::Text m_enterreiniciarText;
};