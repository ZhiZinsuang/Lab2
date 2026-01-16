// user.cpp
#include <iostream>
#include <sstream>
#include "user.h"

using namespace std;

User::User() : id(0), name("player"), win(0), lose(0), allplays(0) {}

User::User(const string& name, int id_b)
    : id(id_b), name(name), win(0), lose(0), allplays(0) {}

User::User(int id, const string& name, int win, int lose, int allp)
    : id(id), name(name), win(win), lose(lose), allplays(allp) {}

User::User(const User& other)
    : id(other.id), name(other.name), win(other.win),
    lose(other.lose), allplays(other.allplays) {}

User::~User() {}

int User::getId() const {
    return id;
}

string User::getName() const {
    return name;
}

int User::getWin() const {
    return win;
}

int User::getLose() const {
    return lose;
}

int User::getAllplays() const {
    return allplays;
}

void User::userWin() {
    win++;
    allplays++;
}

void User::userLose() {
    lose++;
    allplays++;
}

void User::userDeadHeat() {
    allplays++;
}

User& User::operator=(const User& other) {
    if (this != &other) {
        id = other.id;
        name = other.name;
        win = other.win;
        lose = other.lose;
        allplays = other.allplays;
    }
    return *this;
}

bool User::operator==(const User& other) const {
    return id == other.id && name == other.name;
}

bool User::operator!=(const User& other) const {
    return !(*this == other);
}

// Объединение статистики двух пользователей (только статистики, не имен)
User User::operator+(const User& other) const {
    return User(id, name,
        win + other.win,
        lose + other.lose,
        allplays + other.allplays);
}

ostream& operator<<(ostream& os, const User& user) {
    os << "User ID: " << user.id
        << ", Name: " << user.name
        << ", Wins: " << user.win
        << ", Losses: " << user.lose
        << ", Total plays: " << user.allplays;
    return os;
}

string formatUserStats(const User& user) {
    stringstream ss;
    ss << "Player: " << user.name
        << " (ID: " << user.id << ")\n"
        << "Wins: " << user.win << " | "
        << "Losses: " << user.lose << " | "
        << "Total: " << user.allplays << "\n"
        << "Win rate: "
        << (user.allplays > 0 ? (user.win * 100.0 / user.allplays) : 0)
        << "%";
    return ss.str();
}

// Реализация класса AdvancedUser
AdvancedUser::AdvancedUser(const string& name, int id_b, const string& role)
    : User(name, id_b), role(role) {
    // Вызов конструктора базового класса уже выполнен в списке инициализации
}

AdvancedUser::AdvancedUser(const AdvancedUser& other)
    : User(other), role(other.role) {
    // Копирование данных базового класса и дочернего
}

string AdvancedUser::getRole() const {
    return role;
}

string AdvancedUser::getType() const {
    return "Advanced User (" + role + ")";
}