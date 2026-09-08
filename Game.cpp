#include "Game.h"
#include "AudioManager.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <string>

namespace {
    const std::string kConfigFile = "config.txt";
    const std::string kSaveFile = "partida_guardada.txt";
    const std::string kLegacySaveFile = "savegame.txt";

    int clampVolume(int value) {
        if (value < 0) return 0;
        if (value > 100) return 100;
        return value;
    }
}

Game::Game(Scene* scene, int score)
    : m_score(score)
    , m_continueAvailable(false)
    , m_playerInitials("AAA")
    , m_masterVolume(100)
    , m_musicVolume(100)
    , m_sfxVolume(100)
    , m_hudSize(100)
    , m_win(sf::VideoMode(800, 600), "Ciruja Invaders")
    , m_scene(scene)
{
    m_win.setFramerateLimit(60);
    loadConfigFromFile();
    applyVolumeToAudio();

    std::string initials;
    int savedScore = 0;
    int level = 1;
    int wave = 0;
    int lives = 3;
    if (loadSaveGameFromFile(initials, savedScore, level, wave, lives)) {
        m_continueAvailable = true;
        m_score = savedScore;
        m_playerInitials = initials;
    }
}

Game::~Game() {
    saveConfigToFile();
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

void Game::setMasterVolume(int volume) {
    m_masterVolume = clampVolume(volume);
    applyVolumeToAudio();
    saveConfigToFile();
}

int Game::getMasterVolume() const {
    return m_masterVolume;
}

void Game::setMusicVolume(int volume) {
    m_musicVolume = clampVolume(volume);
    applyVolumeToAudio();
    saveConfigToFile();
}

int Game::getMusicVolume() const {
    return m_musicVolume;
}

void Game::setSfxVolume(int volume) {
    m_sfxVolume = clampVolume(volume);
    applyVolumeToAudio();
    saveConfigToFile();
}

int Game::getSfxVolume() const {
    return m_sfxVolume;
}

void Game::setHudSize(int size) {
    m_hudSize = clampVolume(size);
    saveConfigToFile();
}

int Game::getHudSize() const {
    return m_hudSize;
}

void Game::applyVolumeToAudio() const {
    AudioManager::instance().setMasterVolume(m_masterVolume);
    AudioManager::instance().setMusicVolume(m_musicVolume);
    AudioManager::instance().setSfxVolume(m_sfxVolume);
}

void Game::loadConfigFromFile() {
    std::ifstream input(kConfigFile.c_str());
    if (!input.is_open()) {
        return;
    }

    std::string line;
    while (std::getline(input, line)) {
        if (line.empty()) {
            continue;
        }
        const std::string::size_type pos = line.find('=');
        if (pos == std::string::npos) {
            continue;
        }
        const std::string key = line.substr(0, pos);
        const std::string value = line.substr(pos + 1);
        std::istringstream iss(value);
        int numericValue = 0;
        iss >> numericValue;

        if (key == "master") {
            m_masterVolume = clampVolume(numericValue);
        } else if (key == "music") {
            m_musicVolume = clampVolume(numericValue);
        } else if (key == "sfx") {
            m_sfxVolume = clampVolume(numericValue);
        } else if (key == "hud") {
            m_hudSize = clampVolume(numericValue);
        }
    }
}

void Game::saveConfigToFile() const {
    std::ofstream output(kConfigFile.c_str(), std::ios::out | std::ios::trunc);
    if (!output.is_open()) {
        return;
    }

    output << "master=" << m_masterVolume << "\n";
    output << "music=" << m_musicVolume << "\n";
    output << "sfx=" << m_sfxVolume << "\n";
    output << "hud=" << m_hudSize << "\n";
}

bool Game::loadSaveGameFromFile(std::string& initials, int& score, int& level, int& wave, int& lives) const {
    std::ifstream input(kSaveFile.c_str());
    if (!input.is_open()) {
        input.open(kLegacySaveFile.c_str());
    }
    if (!input.is_open()) {
        return false;
    }

    initials.clear();
    score = 0;
    level = 1;
    wave = 0;
    lives = 3;
    input >> initials >> score >> level >> wave >> lives;
    return (!initials.empty() && input.good());
}

void Game::saveGameState(const std::string& initials, int score, int level, int wave, int lives) const {
    std::ofstream output(kSaveFile.c_str(), std::ios::out | std::ios::trunc);
    if (!output.is_open()) {
        return;
    }

    output << initials << "\n";
    output << score << "\n";
    output << level << "\n";
    output << wave << "\n";
    output << lives << "\n";
}

void Game::clearSavedGame() const {
    std::remove(kSaveFile.c_str());
    std::remove(kLegacySaveFile.c_str());
}
