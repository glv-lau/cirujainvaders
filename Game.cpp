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
            m_scene->onEnter(*this);
        }
    }
}

void Game::setScene(Scene* nextScene) {
    m_nextScene = nextScene;
}
void Game::setmusicvolume(int volume) {
    musicVolume = volume;
    m_music.setVolume(volume*static_cast<float>(masterVolume) / 100.0f);
}
int Game::getmusicvolume() const {
    return musicVolume;
}

void Game::enableMusic(bool enabled)
{
    m_musicEnabled = enabled;

    if (enabled)
        m_music.play();
    else
        m_music.stop();
}
void Game::playmusic(const std::string& filename, int volume, bool loop) {
    if (m_music.openFromFile(filename)) {
        m_music.setVolume(static_cast<float>(volume*masterVolume) / 100.0f);
        m_music.setLoop(loop);
        m_music.play();
    }
}

void game::setsfxvolume(int volume) {
    sfxVolume = volume;
    m_sfx.setVolume(volume*static_cast<float>(masterVolume) / 100.0f);
}
int getsfxvolume() const {
    return sfxVolume;
}

void game::setmastvolume(int volume) {
    masterVolume = volume;
    m_master.setVolume(volume);
}
int getmastvolume() const {
    return masterVolume;
}

void setHudSize(int size) {
    HudSize = size;
}
int getHudSize() const {
    return HudSize;
}