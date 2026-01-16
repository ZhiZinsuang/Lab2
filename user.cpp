
#include <iostream>
#include <sstream>
#include "user.h"

using namespace std;

User::User() : PlayerBase("player"), id(0), win(0), lose(0), allplays(0) {}

User::User(const string& name, int id_b)
    : PlayerBase(name), id(id_b), win(0), lose(0), allplays(0) {}

User::User(int id, const string& name, int win, int lose, int allp)
    : PlayerBase(name), id(id), win(win), lose(lose), allplays(allp) {}

User::User(const User& other)
    : PlayerBase(other.name), id(other.id), win(other.win),
    lose(other.lose), allplays(other.allplays) {}

User::~User() {}

int User::getId() const {
    return id;
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
        // Копируем имя из базового класса
        name = other.name; // name наследуется из PlayerBase
        id = other.id;
        win = other.win;
        lose = other.lose;
        allplays = other.allplays;
    }
    return *this;
}

bool User::operator==(const User& other) const {
    return id == other.id && name == other.name; // name из PlayerBase
}

bool User::operator!=(const User& other) const {
    return !(*this == other);
}

User User::operator+(const User& other) const {
    return User(id, name,
        win + other.win,
        lose + other.lose,
        allplays + other.allplays);
}

ostream& operator<<(ostream& os, const User& user) {
    os << "User ID: " << user.id
        << ", Name: " << user.name  // name доступен, так как operator<< дружественный
        << ", Wins: " << user.win
        << ", Losses: " << user.lose
        << ", Total plays: " << user.allplays;
    return os;
}

string formatUserStats(const User& user) {
    stringstream ss;
    ss << "Player: " << user.name  // name доступен, так как функция дружественная
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
    // Вызов конструктора базового класса User выполняется в списке инициализации
    // который в свою очередь вызывает конструктор PlayerBase
}

AdvancedUser::AdvancedUser(const AdvancedUser& other)
    : User(other), role(other.role) {
    // Копирование данных базового класса User и дочернего
}

string AdvancedUser::getRole() const {
    return role;
}