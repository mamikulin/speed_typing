#include "TextBox.hpp"

TextBox::TextBox(float x, float y, float width, float height, sf::Font& font) {
    box.setSize(sf::Vector2f(width, height));
    box.setPosition(x, y);
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(1);

    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    text.setPosition(x + 5, y + 5);
}

void TextBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
}

void TextBox::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));
        isActive = box.getGlobalBounds().contains(mousePos);
    }

    if (isActive && event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b') { // Backspace
            if (!input.empty()) {
                input.pop_back();
            }
        } else if (event.text.unicode < 128) {
            input += static_cast<char>(event.text.unicode);
        }
        text.setString(input);
    }
}

std::string TextBox::getText() const {
    return input;
}

void TextBox::setText(const std::string& str) {
    input = str;
    text.setString(input);
}

void TextBox::clear() {
    input.clear();
    text.setString("");
}
