#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "TextBox.hpp"
#include "UserManager.hpp"
#include "ModeStrategy.hpp"

class Menu {
public:
    Menu();
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    Button registerButton;
    Button loginButton;
    Button startButton;
    Button resultsButton;
    Button confirmButton;
    Button backButton;
    TextBox loginBox;
    TextBox passwordBox;
    UserManager userManager;
    bool isEnteringCredentials;
    bool showResults;
    ModeStrategy* modeStrategy;

    void processEvents();
    void render();
    void createButton(Button& button, const std::string& text, float x, float y);
    void handleMouseClick(const sf::Vector2i& mousePos, sf::Event& event);
    void displayResults();
};

#endif // MENU_HPP
