#ifndef SCENEHIGHSCORES_H
#define SCENEHIGHSCORES_H

#include "Scene.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class SceneHighScores : public Scene {
public:
    SceneHighScores();
    ~SceneHighScores() override = default;

    void handleEvent(const sf::Event& event, Game& game) override;
    void update(float dt, Game& game) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Font m_font;
    sf::Text m_titleText;
    sf::Text m_scoresText;
    sf::Text m_exitText;
    bool m_fontLoaded;
};

#endif
