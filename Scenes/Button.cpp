#include "Button.h"

Button::Button(const sf::Font& font, const std::string& text, const sf::Vector2f& position, const sf::Vector2f& size)
    : m_box(size)
    , m_text(text, font, 20)
{
    m_box.setPosition(position);
    m_box.setFillColor(sf::Color::White);
    m_box.setOutlineColor(sf::Color::Black);
    m_box.setOutlineThickness(2.f);

    m_text.setFillColor(sf::Color::Black);
    const sf::FloatRect bounds = m_text.getLocalBounds();
    m_text.setPosition(
        position.x + (size.x - bounds.width) / 2.f,
        position.y + (size.y - bounds.height) / 2.f - 5.f);
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(m_box);
    window.draw(m_text);
}

void Button::update() {
}

bool Button::contains(const sf::Vector2f& mousePos) const {
    return m_box.getGlobalBounds().contains(mousePos);
}

void Button::setSelected(bool selected) {
    m_isPressed = selected;
    m_box.setFillColor(selected ? sf::Color(9, 121, 176) : sf::Color::White);
}
