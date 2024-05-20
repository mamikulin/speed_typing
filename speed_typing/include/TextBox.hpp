#ifndef TEXTBOX_HPP
#define TEXTBOX_HPP

#include <SFML/Graphics.hpp>
#include <string>

class TextBox {
public:
    TextBox(float x, float y, float width, float height, sf::Font& font);

    void draw(sf::RenderWindow& window);
    void handleEvent(sf::Event& event);
    std::string getText() const;
    void setText(const std::string& str);
    void clear();

private:
    sf::RectangleShape box;
    sf::Text text;
    std::string input;
    bool isActive = false;
};

#endif // TEXTBOX_HPP
