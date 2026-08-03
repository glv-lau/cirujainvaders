#include "Game.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

Game::Game(Scene* scene, int score)
    : m_score(score)
    , m_win(sf::VideoMode(800, 600), "Ciruja Invaders")
    , m_scene(scene)
{
    m_win.setFramerateLimit(60);
}

Game::~Game() {
    delete m_scene;
}

void Game::play() {
    sf::Clock clock;

    while (m_win.isOpen()) {
        const float dt = clock.restart().asSeconds();

        sf::Event event;
        while (m_win.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                m_win.close();
            }
            if (m_scene) {
                m_scene->handleEvent(event, *this);
            }
        }

        if (m_scene) {
            m_scene->update(dt, *this);
            m_win.clear(sf::Color(220, 220, 180));
            m_scene->draw(m_win);
            m_win.display();
        }

        if (m_nextScene) {
            delete m_scene;
            m_scene = m_nextScene;
            m_nextScene = nullptr;
        }
    }
}

void Game::setScene(Scene* nextScene) {
    m_nextScene = nextScene;
}
