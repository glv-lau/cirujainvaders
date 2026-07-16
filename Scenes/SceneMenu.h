#ifndef SCENEMENU_H
#define SCENEMENU_H

#include "Scenes/Scene.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

class SceneMenu : public Scene {
public:
    SceneMenu();
    ~SceneMenu() override = default;

    void update(float dt, Game& game) override;
    void draw(sf::RenderWindow& window) override;

private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_startText;
    sf::Text m_exitText;
    bool m_fontLoaded = false;
};

#endif
