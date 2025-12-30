#ifndef NON_EXISTENT_USER_EXEPTION_H
#define NON_EXISTENT_USER_EXEPTION_H

#include <iostream>

using namespace std;

class NonExistentUserException {
private:
    std::string message;
public:
    NonExistentUserException(const std::string& message) :message(message) {}
    std::string getMessage() { return message; }
};


#endif // !NON_EXISTENT_USER_EXEPTION_H
