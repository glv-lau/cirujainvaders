#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>

class AudioManager {
public:
    static AudioManager& instance();

    void setMasterVolume(int volume);
    int getMasterVolume() const;
    void setMusicVolume(int volume);
    int getMusicVolume() const;
    void setSfxVolume(int volume);
    int getSfxVolume() const;

    void setMusicEnabled(bool enabled);
    void setSfxEnabled(bool enabled);
    bool isMusicEnabled() const;
    bool isSfxEnabled() const;

    void playMusic(const std::string& fileName, bool loop = true);
    void playSfx(const std::string& fileName);

private:
    AudioManager();
    int m_masterVolume;
    int m_musicVolume;
    int m_sfxVolume;
    bool m_musicEnabled;
    bool m_sfxEnabled;
    std::string m_lastTrack;
    sf::Music m_music;
    sf::SoundBuffer m_sfxBuffer;
    sf::Sound m_sfxSound;
};

#endif
