#ifndef SCENE_H
#define SCENE_H

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class Game;

class Scene {
public:
    virtual ~Scene() = default;

    virtual void handleEvent(const sf::Event& event, Game& game) { (void)event; (void)game; }
    virtual void update(float dt, Game& game) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void onEnter(Game& game) { (void)game; }
};

#endif
