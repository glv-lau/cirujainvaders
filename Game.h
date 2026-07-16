#ifndef GAME_H
#define GAME_H

#include "Scenes/Scene.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Game {
public:
    Game(Scene* scene, int score = 0);
    ~Game();

    void play();
    void setScene(Scene* nextScene);

    sf::RenderWindow& getWindow() { return m_win; }
    int getScore() const { return m_score; }
    void addScore(int points) { m_score += points; }

private:
    int m_score;
    sf::RenderWindow m_win;
    Scene* m_scene;
    Scene* m_nextScene = nullptr;
};

#endif
