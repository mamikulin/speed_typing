#ifndef MODESTRATEGY_HPP
#define MODESTRATEGY_HPP

#include "UserManager.hpp"
#include "TextBox.hpp"

class ModeStrategy {
public:
    virtual void handleConfirmation(const std::string& login, const std::string& password, bool& isEnteringCredentials, TextBox& loginBox, TextBox& passwordBox) = 0;
    virtual ~ModeStrategy() {}
};

class RegisterMode : public ModeStrategy {
public:
    RegisterMode(UserManager& userManager, TextBox& loginBox, TextBox& passwordBox);

    void handleConfirmation(const std::string& login, const std::string& password, bool& isEnteringCredentials, TextBox& loginBox, TextBox& passwordBox) override;

private:
    UserManager& userManager;
    TextBox& loginBox;
    TextBox& passwordBox;
};

class LoginMode : public ModeStrategy {
public:
    LoginMode(UserManager& userManager, TextBox& loginBox, TextBox& passwordBox);

    void handleConfirmation(const std::string& login, const std::string& password, bool& isEnteringCredentials, TextBox& loginBox, TextBox& passwordBox) override;

private:
    UserManager& userManager;
    TextBox& loginBox;
    TextBox& passwordBox;
};

#endif // MODESTRATEGY_HPP
