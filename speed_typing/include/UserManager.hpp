#ifndef USERMANAGER_HPP
#define USERMANAGER_HPP

#include "User.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <iostream>

class UserManager {
public:
    UserManager();
    bool registerUser(const std::string& login, const std::string& password);
    bool loginUser(const std::string& login, const std::string& password);
    std::unordered_map<std::string, User>& getUsers();

private:
    std::unordered_map<std::string, User> users;
    void loadUsers();
    void saveUsers();
};

#endif // USERMANAGER_HPP
