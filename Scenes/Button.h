#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

class Button {
public:
    Button(const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size);
    ~Button() = default;

    void draw(sf::RenderWindow& window);
    void update();

    bool contains(const sf::Vector2f& mousePos) const;
    void setSelected(bool selected);

private:
    bool m_isPressed = false;
    sf::RectangleShape m_box;
    sf::Text m_text;
};

#endif
