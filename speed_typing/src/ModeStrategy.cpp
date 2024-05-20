#include "ModeStrategy.hpp"
#include <iostream>

RegisterMode::RegisterMode(UserManager& userManager, TextBox& loginBox, TextBox& passwordBox)
    : userManager(userManager), loginBox(loginBox), passwordBox(passwordBox) {}

void RegisterMode::handleConfirmation(const std::string& login, const std::string& password, bool& isEnteringCredentials, TextBox& loginBox, TextBox& passwordBox) {
    if (userManager.registerUser(login, password)) {
        std::cout << "Registration successful!\n";
    } else {
        std::cout << "User already exists!\n";
    }
    isEnteringCredentials = false;
    loginBox.clear();
    passwordBox.clear();
}

LoginMode::LoginMode(UserManager& userManager, TextBox& loginBox, TextBox& passwordBox)
    : userManager(userManager), loginBox(loginBox), passwordBox(passwordBox) {}

void LoginMode::handleConfirmation(const std::string& login, const std::string& password, bool& isEnteringCredentials, TextBox& loginBox, TextBox& passwordBox) {
    if (userManager.loginUser(login, password)) {
        std::cout << "Login successful!\n";
    } else {
        std::cout << "Invalid login or password!\n";
    }
    isEnteringCredentials = false;
    loginBox.clear();
    passwordBox.clear();
}
