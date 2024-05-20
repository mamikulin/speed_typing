#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <algorithm>

class User {
public:
    std::string login;
    std::string password;
    int speed;
    int fewestErrors;

    User();
    User(const std::string& login, const std::string& password);
    std::string toString() const;
    static User fromString(const std::string& str);

private:
    static void ltrim(std::string& s);
    static void rtrim(std::string& s);
    static void trim(std::string& s);
};

#endif // USER_HPP
