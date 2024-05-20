#include "User.hpp"

User::User() : speed(0), fewestErrors(9999) {}

User::User(const std::string& login, const std::string& password)
    : login(login), password(password), speed(0), fewestErrors(9999) {}

std::string User::toString() const {
    return login + " - " + password + " - " + std::to_string(speed) + " - " + std::to_string(fewestErrors);
}

User User::fromString(const std::string& str) {
    size_t pos1 = str.find(" - ");
    size_t pos2 = str.find(" - ", pos1 + 3);
    size_t pos3 = str.find(" - ", pos2 + 3);

    if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos) {
        throw std::invalid_argument("Invalid format");
    }

    std::string login = str.substr(0, pos1);
    std::string password = str.substr(pos1 + 3, pos2 - pos1 - 3);
    int speed = std::stoi(str.substr(pos2 + 3, pos3 - pos2 - 3));
    int fewestErrors = std::stoi(str.substr(pos3 + 3));

    trim(login);
    trim(password);

    User user(login, password);
    user.speed = speed;
    user.fewestErrors = fewestErrors;

    return user;
}

void User::ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void User::rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void User::trim(std::string& s) {
    ltrim(s);
    rtrim(s);
}
