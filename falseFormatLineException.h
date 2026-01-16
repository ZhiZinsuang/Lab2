#ifndef FALSE_FORMAT_LINE_EXEPTION
#define FALSE_FORMAT_LINE_EXEPTION

#include <iostream>
#include "baseException.h"

using namespace std;

class FalseFormatLineException : public BaseException {
public:
    FalseFormatLineException(const std::string& message) : BaseException(message) {}
};

#endif // !FALSE_FORMAT_LINE_EXEPTION