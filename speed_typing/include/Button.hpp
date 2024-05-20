#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

struct Button {
    sf::RectangleShape shape;
    sf::Text text;

    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2f& mousePos);
};

#endif // BUTTON_HPP
