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
    void playmusic(const std::string& filename, int volume = 100, bool loop = true);
    void stopmusic();
    void setmusicvolume(int volume);
    int getmusicvolume() const;
    void setsfxvolume(int volume);
    int getsfxvolume() const;
    void setmastvolume(int volume);
    int getmastvolume() const;

    void enableMusic(bool enabled);
    bool ismusicEnabled() const { return m_musicEnabled; }
private:
    int m_score;
    sf::RenderWindow m_win;
    Scene* m_scene;
    Scene* m_nextScene = nullptr;
    //Música de fondo, efectos de sonido, etc.
    sf::Music m_music;
    sf::Sound m_sfx;
    int masterVolume = 100;
    float musicVolume = 100;
    float sfxVolume = 100;

    bool m_musicEnabled = true;
    bool m_sfxEnabled = true;
    //HUD
    int HudSize = 50;
};

#endif
