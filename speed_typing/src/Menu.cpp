#include "Menu.hpp"
#include "ResourcePath.hpp"
#include <iostream>
#include <algorithm>

Menu::Menu()
    : window(sf::VideoMode(800, 600), "Menu"),
      font(),
      registerButton(),
      loginButton(),
      startButton(),
      resultsButton(),
      confirmButton(),
      backButton(),
      loginBox(300, 250, 200, 40, font),
      passwordBox(300, 300, 200, 40, font),
      userManager(),
      isEnteringCredentials(false),
      showResults(false),
      modeStrategy(nullptr) {
    window.setFramerateLimit(60);
    if (!font.loadFromFile(resourcePath()+"Roboto-BoldItalic.ttf")) {
        std::cerr << "Error loading font\n";
        exit(1);
    }
    createButton(registerButton, "Register", 300, 100);
    createButton(loginButton, "Login", 300, 200);
    createButton(startButton, "Start Training", 300, 300);
    createButton(resultsButton, "Results", 300, 400);
    createButton(confirmButton, "Confirm", 300, 350);
    createButton(backButton, "Back", 700, 550);

    window.setFramerateLimit(60); // Ограничение FPS
}

void Menu::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void Menu::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::TextEntered) {
            handleMouseClick(sf::Mouse::getPosition(window), event);
        }
    }
}

void Menu::render() {
    window.clear(sf::Color::White);

    if (isEnteringCredentials) {
        loginBox.draw(window);
        passwordBox.draw(window);
        confirmButton.draw(window);
    } else if (showResults) {
        displayResults();
        backButton.draw(window);
    } else {
        registerButton.draw(window);
        loginButton.draw(window);
        startButton.draw(window);
        resultsButton.draw(window);
    }

    window.display();
}

void Menu::createButton(Button& button, const std::string& text, float x, float y) {
    button.shape.setSize(sf::Vector2f(200, 50));
    button.shape.setPosition(x, y);
    button.shape.setFillColor(sf::Color::Green);

    button.text.setFont(font);
    button.text.setString(text);
    button.text.setCharacterSize(24);
    button.text.setFillColor(sf::Color::Black);
    button.text.setPosition(x + 10, y + 10);
}

void Menu::handleMouseClick(const sf::Vector2i& mousePos, sf::Event& event) {
    sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    if (isEnteringCredentials) {
        loginBox.handleEvent(event);
        passwordBox.handleEvent(event);

        if (confirmButton.isClicked(mousePosF)) {
            if (modeStrategy) {
                modeStrategy->handleConfirmation(loginBox.getText(), passwordBox.getText(), isEnteringCredentials, loginBox, passwordBox);
                delete modeStrategy;
                modeStrategy = nullptr;
            }
        }
    } else {
        if (registerButton.isClicked(mousePosF)) {
            isEnteringCredentials = true;
            modeStrategy = new RegisterMode(userManager, loginBox, passwordBox);
        } else if (loginButton.isClicked(mousePosF)) {
            isEnteringCredentials = true;
            modeStrategy = new LoginMode(userManager, loginBox, passwordBox);
        } else if (resultsButton.isClicked(mousePosF)) {
            showResults = true;
        } else if (showResults && backButton.isClicked(mousePosF)) {
            showResults = false;
        }
    }
}

void Menu::displayResults() {
    std::vector<User> users;
    for (const auto& pair : userManager.getUsers()) {
        users.push_back(pair.second);
    }

    std::sort(users.begin(), users.end(), [](const User& a, const User& b) {
        if (a.speed != b.speed) {
            return a.speed > b.speed;
        }
        return a.fewestErrors < b.fewestErrors;
    });

    float y = 50;
    for (const auto& user : users) {
        sf::Text userText;
        userText.setFont(font);
        userText.setString(user.login + " - Speed: " + std::to_string(user.speed) + " - Errors: " + std::to_string(user.fewestErrors));
        userText.setCharacterSize(24);
        userText.setFillColor(sf::Color::Black);
        userText.setPosition(50, y);
        window.draw(userText);
        y += 30;
    }

    backButton.draw(window);
}
