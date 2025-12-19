#ifndef EXITING_USER_EXEPTION
#define EXITING_USER_EXEPTION

#include <iostream>

class ExistingUserException {
private:
    std::string message;
public:
    ExistingUserException(const std::string& message) :message(message) {}
    std::string getMessage() { return message; }
};

#endif