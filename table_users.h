
#ifndef TABLE_USERS_H
#define TABLE_USERS_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "user.h"

class Table_users {
private:
    std::string file_r;
    std::vector<std::unique_ptr<User>> users; // Используем unique_ptr
public:
    Table_users();
    Table_users(const std::string& f);
    Table_users(const Table_users& other); // Конструктор копирования
    ~Table_users();

    void out() const;
    void readfile();
    void newUser(const std::string& name);
    bool duplicateName(const std::string& name) const;
    int countUsers() const;
    void rewrightFile();
    User& getUser(int id);
    const User& getUser(int id) const;

    // Перегрузка операторов
    Table_users& operator=(const Table_users& other);
    User* operator[](size_t index);
    const User* operator[](size_t index) const;
    friend std::ostream& operator<<(std::ostream& os, const Table_users& table);

    // Поиск пользователя по имени (регистронезависимый)
    User* findUserByName(const std::string& name) const;

    // Добавление AdvancedUser
    void newAdvancedUser(const std::string& name, const std::string& role);
};

#endif