#ifndef NON_EXISTENT_USER_EXEPTION_H
#define NON_EXISTENT_USER_EXEPTION_H

#include <iostream>
#include "baseException.h"

using namespace std;

class NonExistentUserException : public BaseException {
public:
    NonExistentUserException(const std::string& message) : BaseException(message) {}
};


#endif // !NON_EXISTENT_USER_EXEPTION_H
