#include "Menu.hpp"
#include "ResourcePath.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
std::string give_message() {
    std::vector<std::string> messages = {
        "Keep going!",
        "You're doing great!",
        "Almost there!",
        "Stay focused!",
        "Push your limits!"
    };
    
    std::string randomMessage = messages[std::rand() % messages.size()];
    return randomMessage;
}


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
      modeStrategy(nullptr),
      timerRunning(false),
      count(0),
      s(0),
      k(0),
      mistakes(0) {
    window.setFramerateLimit(24);
    if (!font.loadFromFile(resourcePath() + "Roboto-BoldItalic.ttf")) {
        std::cerr << "Error loading font\n";
        exit(1);
    }
    createButton(registerButton, "Register", 300, 100);
    createButton(loginButton, "Login", 300, 200);
    createButton(startButton, "Start Training", 300, 300);
    createButton(resultsButton, "Results", 300, 400);
    createButton(confirmButton, "Confirm", 300, 350);
    createButton(backButton, "Back", 700, 550);

    // Initialize texts for training mode
    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::Black);
    timerText.setPosition(500, 16);
    
    resultsText.setFont(font);
    resultsText.setCharacterSize(20); // in pixels, not points!
    resultsText.setFillColor(sf::Color::Black);
    resultsText.setPosition(500, 48); // Position under the timer
    
    messageText.setFont(font);
    messageText.setCharacterSize(40); // in pixels, not points!
    messageText.setFillColor(sf::Color::Red);
    messageText.setString(give_message());
    sf::FloatRect messageRect = messageText.getLocalBounds();
    messageText.setOrigin(messageRect.left + messageRect.width / 2.0f, messageRect.top + messageRect.height / 2.0f);
    messageText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    
    userInputText.setFont(font);
    userInputText.setCharacterSize(30); // in pixels, not points!
    userInputText.setFillColor(sf::Color::Blue);
    userInputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f - 50);
          sf::Image icon;
          if (!icon.loadFromFile(resourcePath() + "icon.png")) {
              return EXIT_FAILURE;
          }
          window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
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

        if (timerRunning) {
            handleTrainingEvents(event);
        }
    }
}

void Menu::handleTrainingEvents(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        timerRunning = false;
    }

    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter && timerRunning) {
        elapsed = clock.getElapsedTime();
        timerRunning = false;
        presses.push_back(count);
        count = 0;
    }

    if (event.type == sf::Event::TextEntered && timerRunning) {
        if (event.text.unicode < 128) {
            char typedChar = static_cast<char>(event.text.unicode);
            if (typedChar == '\b' && !userInput.empty()) {
                userInput.pop_back();
                k--;
                count--;
            } else if (typedChar != '\b') {
                if (typedChar == messageText.getString()[k]) {
                    userInput += typedChar;
                    k++;
                    count++;
                    if (k == messageText.getString().getSize()) {
                        
                        messageText.setString(give_message());
                        k = 0;
                        userInput.clear();
                    }
                } else {
                    mistakes++;
                }
            }
        }
        userInputText.setString(userInput);
        sf::FloatRect userInputRect = userInputText.getLocalBounds();
        userInputText.setOrigin(userInputRect.left + userInputRect.width / 2.0f, userInputRect.top + userInputRect.height / 2.0f);
        userInputText.setPosition(window.getSize().x / 2.0f, window.getSize().y / 2.0f + 50);
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
    } else if (timerRunning) {
        updateTraining();
        drawTraining();
    } else {
        registerButton.draw(window);
        loginButton.draw(window);
        startButton.draw(window);
        resultsButton.draw(window);
    }

    window.display();
}


void Menu::startTraining() {
    timerRunning = true;
    clock.restart();
    userInput.clear();
    userInputText.setString(userInput);
    k = 0;
    messageText.setString(give_message());
}

void Menu::updateTraining() {
    if (timerRunning) {
        elapsed = clock.getElapsedTime();
        if (elapsed.asSeconds() >= 30.0f) {
            timerRunning = false;
            presses.push_back(count);
            count = 0;
            userInput.clear();
            userInputText.setString(userInput);
            k = 0;
            messageText.setString(give_message());
        }
    }
    timerText.setString("Timer: " + std::to_string(elapsed.asSeconds()) + "s");

    std::stringstream resultsStream;
    int start = presses.size() > 9 ? presses.size() - 9 : 0;
    for (int i = start; i < presses.size(); ++i) {
        resultsStream << "Result " << i + 1 << ": " << std::fixed << std::setprecision(2) << presses[i] * 2 << " w/m\n";
    }
    resultsText.setString(resultsStream.str());
}

void Menu::drawTraining() {
    window.draw(timerText);
    window.draw(resultsText);
    window.draw(messageText);
    window.draw(userInputText);
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
        } else if (startButton.isClicked(mousePosF)) {
            startTraining();
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
