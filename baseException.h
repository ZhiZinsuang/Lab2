#ifndef BASE_EXEPTION_H
#define BASE_EXEPTION_H

#include <iostream>
#include <string>
#include <memory>

class BaseException {
protected:
    std::string message;
public:
    BaseException(const std::string& msg) : message(msg) {}
    virtual ~BaseException() = default;
    virtual std::string getMessage() const { return message; }
    friend std::ostream& operator<<(std::ostream& os, const BaseException& ex);
}; 
#endif