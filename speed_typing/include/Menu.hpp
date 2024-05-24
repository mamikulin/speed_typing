#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "TextBox.hpp"
#include "UserManager.hpp"
#include "ModeStrategy.hpp"

#include "ResourcePath.hpp"

std::string give_message();

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
    bool timerRunning;
    sf::Clock clock;
    sf::Time elapsed;
    std::vector<int> presses;
    int count;
    int s;
    int k;
    int mistakes;
    std::string userInput;

    sf::Text timerText;
    sf::Text resultsText;
    sf::Text messageText;
    sf::Text userInputText;

    void startTraining();
    void handleTrainingEvents(sf::Event& event);
    void updateTraining();
    void drawTraining();

    void processEvents();
    void render();
    void createButton(Button& button, const std::string& text, float x, float y);
    void handleMouseClick(const sf::Vector2i& mousePos, sf::Event& event);
    void displayResults();
};

#endif // MENU_HPP
