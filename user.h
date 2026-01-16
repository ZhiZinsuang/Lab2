// user.h
#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <memory>

class User {
protected:
    int id;
    std::string name;
    int win;
    int lose;
    int allplays;
public:
    User();
    User(const std::string& name, int id_b);
    User(int id, const std::string& name, int win, int lose, int allp);
    User(const User& other); // Конструктор копирования
    virtual ~User();

    int getId() const;
    std::string getName() const;
    int getWin() const;
    int getLose() const;
    int getAllplays() const;

    void userWin();
    void userLose();
    void userDeadHeat();

    // Перегрузка операторов
    User& operator=(const User& other);
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
    User operator+(const User& other) const; // Объединение статистики
    friend std::ostream& operator<<(std::ostream& os, const User& user);

    // Дружественная функция для форматированного вывода
    friend std::string formatUserStats(const User& user);

    // Виртуальная функция для возможного наследования
    virtual std::string getType() const { return "Base User"; }
};

// Класс-наследник для демонстрации вызова конструктора базового класса
class AdvancedUser : public User {
private:
    std::string role;
public:
    AdvancedUser(const std::string& name, int id_b, const std::string& role);
    AdvancedUser(const AdvancedUser& other);
    std::string getRole() const;
    std::string getType() const override;
};

#endif