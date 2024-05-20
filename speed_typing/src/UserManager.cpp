#include "UserManager.hpp"

const std::string USERS_FILE = "users.txt";

UserManager::UserManager() {
    loadUsers();
}

bool UserManager::registerUser(const std::string& login, const std::string& password) {
    if (users.find(login) == users.end()) {
        User user(login, password);
        users[login] = user;
        saveUsers();
        return true;
    }
    return false;
}

bool UserManager::loginUser(const std::string& login, const std::string& password) {
    auto it = users.find(login);
    return it != users.end() && it->second.password == password;
}

std::unordered_map<std::string, User>& UserManager::getUsers() {
    return users;
}

void UserManager::loadUsers() {
    std::ifstream file(USERS_FILE);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            User user = User::fromString(line);
            users[user.login] = user;
        }
        file.close();
    }
}

void UserManager::saveUsers() {
    std::ofstream file(USERS_FILE);
    if (file.is_open()) {
        for (const auto& pair : users) {
            file << pair.second.toString() << std::endl;
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open " << USERS_FILE << " for writing.\n";
    }
}
