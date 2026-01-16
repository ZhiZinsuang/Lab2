#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <memory>
#include "playerBase.h"

// Делаем User наследником PlayerBase
class User : public PlayerBase {
protected:
    int id;
    int win;
    int lose;
    int allplays;
public:
    User();
    User(const std::string& name, int id_b);
    User(int id, const std::string& name, int win, int lose, int allp);
    User(const User& other);
    virtual ~User() override;

    int getId() const;
    int getWin() const;
    int getLose() const;
    int getAllplays() const;

    void userWin();
    void userLose();
    void userDeadHeat();

    // Перегрузка виртуальных методов
    std::string getType() const override { return "Base User"; }
    void displayInfo() const override {
        PlayerBase::displayInfo(); // Вызов метода базового класса
        std::cout << "ID: " << id << ", Wins: " << win << std::endl;
    }

    // Не виртуальная функция, вызывающая виртуальную
    void showPlayerType() const {
        std::cout << "Player type (via non-virtual function): "
            << getType() << std::endl;
    }

    // Перегрузка операторов
    User& operator=(const User& other);
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
    User operator+(const User& other) const;

    // Перегрузка оператора присваивания для базового класса
    User& operator=(const PlayerBase& other) {
        name = other.getName();
        // Сброс статистики
        win = lose = allplays = 0;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const User& user);
    friend std::string formatUserStats(const User& user);
};

// AdvancedUser с улучшенной перегрузкой
class AdvancedUser : public User {
private:
    std::string role;
public:
    AdvancedUser(const std::string& name, int id_b, const std::string& role);
    AdvancedUser(const AdvancedUser& other);

    std::string getRole() const;

    // Перегрузка с вызовом метода базового класса
    std::string getType() const override {
        return User::getType() + " (Advanced)"; // Вызов метода базового класса
    }

    // Перегрузка без вызова метода базового класса
    void displayInfo() const override {
        // Не вызываем User::displayInfo()
        std::cout << "Advanced User: " << name
            << " [" << role << "]" << std::endl;
    }

    AdvancedUser& operator=(const User& other) {
        User::operator=(other); // Вызов оператора присваивания базового класса
        role = "Default";
        return *this;
    }
};

#endif