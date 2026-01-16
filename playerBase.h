
#ifndef PLAYER_BASE_H
#define PLAYER_BASE_H

#include <iostream>
#include <string>

// Абстрактный базовый класс для игроков
class PlayerBase {
protected:
    std::string name;
public:
    PlayerBase(const std::string& name) : name(name) {}
    virtual ~PlayerBase() = default;

    virtual std::string getType() const = 0; // Чисто виртуальная функция

    virtual void displayInfo() const {
        std::cout << "Player: " << name << std::endl;
    }

    std::string getName() const { return name; }
};

#endif