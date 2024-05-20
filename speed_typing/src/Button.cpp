#include "Button.hpp"

void Button::draw(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(text);
}

bool Button::isClicked(const sf::Vector2f& mousePos) {
    return shape.getGlobalBounds().contains(mousePos);
}
