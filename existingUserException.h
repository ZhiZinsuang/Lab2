#ifndef EXITING_USER_EXEPTION
#define EXITING_USER_EXEPTION

#include <iostream>
#include "baseException.h"

class ExistingUserException : public BaseException {
public:
    ExistingUserException(const std::string& message) : BaseException(message) {}
};

#endif