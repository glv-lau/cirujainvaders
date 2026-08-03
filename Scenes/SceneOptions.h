#ifndef SCENEOPTIONS_H
#define SCENEOPTIONS_H

#include "Scene.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class SceneOptions : public Scene {
public:
    SceneOptions();
    ~SceneOptions() override = default;

    void update(float dt, Game& game) override;
    void draw(sf::RenderWindow& window) override;
    void handleEvent(const sf::Event& event, Game& game) override;
    void onEnter(Game& game) override {
        game.playmusic("menu_music.ogg", m_music, true);
    }
private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_exitText;
    sf::Text m_masterText;
    sf::Text m_musicText;
    sf::Text m_sfxText;
    sf::Text m_hudSizeText;
    bool m_fontLoaded = false;
    int m_selectedOption = 0;
};