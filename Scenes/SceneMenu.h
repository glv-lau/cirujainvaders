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
    void mod_opcion(int valor){
        m_selectedOption += valor;
        if (m_selectedOption < 0) {
            m_selectedOption = 2;
        } else if (m_selectedOption > 2) {
            m_selectedOption = 0;
        }
    }
    int getSelectedOption() const { return m_selectedOption; }
    void handleEvent(const sf::Event& event, Game& game) override;

private:
    sf::Font m_font;
    sf::Text m_title;
    sf::Text m_startText;
    sf::Text m_exitText;
    sf::Text m_optionsText;
    bool m_fontLoaded = false;
    int m_selectedOption = 0;
};

#endif
