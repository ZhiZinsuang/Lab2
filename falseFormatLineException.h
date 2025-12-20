#ifndef FALSE_FORMAT_LINE_EXEPTION
#define FALSE_FORMAT_LINE_EXEPTION

#include <iostream>

using namespace std;

class FalseFormatLineException {
private:
    std::string message;
public:
    FalseFormatLineException(const std::string& message) :message(message) {}
    std::string getMessage() { return message; }
};

#endif // !FALSE_FORMAT_LINE_EXEPTION