#ifndef SCENESTAGEINTRO_H
#define SCENESTAGEINTRO_H

#include "Scene.h"
#include "SceneMatch.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class SceneStageIntro : public Scene {
public:
    SceneStageIntro(int stage = 1, float duration = 1.75f);
    ~SceneStageIntro() override = default;

    void handleEvent(const sf::Event& event, Game& game) override;
    void update(float dt, Game& game) override;
    void draw(sf::RenderWindow& window) override;

private:
    int m_stage;
    float m_timer;
    sf::Font m_font;
    bool m_fontLoaded = false;
    sf::Text m_text;
};

#endif
