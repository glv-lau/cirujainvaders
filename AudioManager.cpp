#include "AudioManager.h"

#include <SFML/Audio.hpp>
#include <iostream>

#if defined(_WIN32)
#include <Windows.h>
#endif

namespace {
    int clampVolume(int value) {
        if (value < 0) return 0;
        if (value > 100) return 100;
        return value;
    }
}

AudioManager::AudioManager()
    : m_masterVolume(100)
    , m_musicVolume(100)
    , m_sfxVolume(100)
    , m_musicEnabled(true)
    , m_sfxEnabled(true)
    , m_lastTrack("")
{
    m_music.setVolume(static_cast<float>(m_musicVolume));
    m_sfxSound.setVolume(static_cast<float>(m_sfxVolume));
}

AudioManager& AudioManager::instance() {
    static AudioManager manager;
    return manager;
}

void AudioManager::setMasterVolume(int volume) {
    m_masterVolume = clampVolume(volume);
    const float master = static_cast<float>(m_masterVolume);
    m_music.setVolume((static_cast<float>(m_musicVolume) / 100.f) * master);
    m_sfxSound.setVolume((static_cast<float>(m_sfxVolume) / 100.f) * master);
}

int AudioManager::getMasterVolume() const {
    return m_masterVolume;
}

void AudioManager::setMusicVolume(int volume) {
    m_musicVolume = clampVolume(volume);
    const float master = static_cast<float>(m_masterVolume);
    m_music.setVolume((static_cast<float>(m_musicVolume) / 100.f) * master);
}

int AudioManager::getMusicVolume() const {
    return m_musicVolume;
}

void AudioManager::setSfxVolume(int volume) {
    m_sfxVolume = clampVolume(volume);
    const float master = static_cast<float>(m_masterVolume);
    m_sfxSound.setVolume((static_cast<float>(m_sfxVolume) / 100.f) * master);
}

int AudioManager::getSfxVolume() const {
    return m_sfxVolume;
}

void AudioManager::setMusicEnabled(bool enabled) {
    m_musicEnabled = enabled;
    if (!m_musicEnabled) {
        m_music.stop();
    }
}

void AudioManager::setSfxEnabled(bool enabled) {
    m_sfxEnabled = enabled;
    if (!m_sfxEnabled) {
        m_sfxSound.stop();
    }
}

bool AudioManager::isMusicEnabled() const {
    return m_musicEnabled;
}

bool AudioManager::isSfxEnabled() const {
    return m_sfxEnabled;
}

void AudioManager::playMusic(const std::string& fileName, bool loop) {
    if (!m_musicEnabled) {
        return;
    }

    if (!m_music.openFromFile(fileName)) {
        std::cerr << "Audio no encontrado: " << fileName << ". Usando fallback de sistema.\n";
#if defined(_WIN32)
        Beep(660, 80);
#endif
        m_lastTrack = fileName;
        return;
    }

    m_music.setLoop(loop);
    m_music.setVolume((static_cast<float>(m_musicVolume) / 100.f) * static_cast<float>(m_masterVolume));
    m_music.play();
    m_lastTrack = fileName;
}

void AudioManager::playSfx(const std::string& fileName) {
    if (!m_sfxEnabled) {
        return;
    }

    if (!m_sfxBuffer.loadFromFile(fileName)) {
        std::cerr << "SFX no encontrado: " << fileName << ". Fallback generado.\n";
#if defined(_WIN32)
        Beep(440, 50);
#endif
        return;
    }

    m_sfxSound.setBuffer(m_sfxBuffer);
    m_sfxSound.setVolume((static_cast<float>(m_sfxVolume) / 100.f) * static_cast<float>(m_masterVolume));
    m_sfxSound.play();
}
