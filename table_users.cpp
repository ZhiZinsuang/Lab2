
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include <cctype>
#include "table_users.h"
#include "existingUserException.h"
#include "falseFormatLineException.h"
#include "nonExistentUserException.h"

using namespace std;

// Вспомогательная функция для регистронезависимого сравнения
bool caseInsensitiveCompare(const string& str1, const string& str2) {
    if (str1.length() != str2.length()) return false;

    return equal(str1.begin(), str1.end(), str2.begin(),
        [](char c1, char c2) {
            return tolower(c1) == tolower(c2);
        });
}

Table_users::Table_users() {}

Table_users::Table_users(const string& f) : file_r(f) {
    try {
        readfile();
    }
    catch (const FalseFormatLineException& e) {
        cout << e.getMessage() << endl;
    }
}

Table_users::Table_users(const Table_users& other) : file_r(other.file_r) {
    // Глубокое копирование unique_ptr
    for (const auto& user : other.users) {
        // Для копирования нужно знать тип объекта
        if (auto advancedUser = dynamic_cast<AdvancedUser*>(user.get())) {
            users.push_back(make_unique<AdvancedUser>(*advancedUser));
        }
        else {
            users.push_back(make_unique<User>(*user));
        }
    }
}

Table_users::~Table_users() {
    rewrightFile();
}

void Table_users::out() const {
    if (users.empty()) {
        cout << "File is empty" << endl;
    }
    else {
        for (const auto& p : users) {
            cout << *p << endl;
        }
    }
}

void Table_users::readfile() {
    ifstream file(file_r);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    try {
        string line;
        while (getline(file, line)) {
            // Используем stringstream для безопасного парсинга
            stringstream ss(line);
            string line1, line2, line3, line4, line5;

            if (!(ss >> line1 >> line2 >> line3 >> line4 >> line5)) {
                throw FalseFormatLineException("Строка в файле неверного формата: " + line);
            }

            // Проверяем, есть ли еще данные в строке
            string extra;
            if (ss >> extra) {
                throw FalseFormatLineException("Лишние данные в строке: " + line);
            }

            users.push_back(make_unique<User>(
                stoi(line1), line2,
                stoi(line3), stoi(line4), stoi(line5)
                ));
        }
    }
    catch (const exception& e) {
        throw FalseFormatLineException(string("Ошибка чтения файла: ") + e.what());
    }

    file.close();
}

bool Table_users::duplicateName(const string& name) const {
    return any_of(users.begin(), users.end(),
        [&name](const unique_ptr<User>& user) {
            return caseInsensitiveCompare(user->getName(), name);
        });
}

void Table_users::newUser(const string& name) {
    if (duplicateName(name)) {
        throw ExistingUserException("User had already created: " + name);
    }
    else {
        users.push_back(make_unique<User>(name, countUsers()));
    }
}

int Table_users::countUsers() const {
    return static_cast<int>(users.size());
}

void Table_users::rewrightFile() {
    ofstream out(file_r);
    if (!out.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    for (const auto& u : users) {
        out << u->getId() << " "
            << u->getName() << " "
            << u->getWin() << " "
            << u->getLose() << " "
            << u->getAllplays() << endl;
    }

    out.close();
}

User& Table_users::getUser(int id) {
    if (id < 0 || id >= static_cast<int>(users.size())) {
        throw NonExistentUserException("Запрашивается несуществующий пользователь с ID: " + to_string(id));
    }
    return *users[id];
}

const User& Table_users::getUser(int id) const {
    if (id < 0 || id >= static_cast<int>(users.size())) {
        throw NonExistentUserException("Запрашивается несуществующий пользователь с ID: " + to_string(id));
    }
    return *users[id];
}

Table_users& Table_users::operator=(const Table_users& other) {
    if (this != &other) {
        file_r = other.file_r;
        users.clear();
        for (const auto& user : other.users) {
            if (auto advancedUser = dynamic_cast<AdvancedUser*>(user.get())) {
                users.push_back(make_unique<AdvancedUser>(*advancedUser));
            }
            else {
                users.push_back(make_unique<User>(*user));
            }
        }
    }
    return *this;
}

User* Table_users::operator[](size_t index) {
    if (index >= users.size()) {
        return nullptr;
    }
    return users[index].get();
}

const User* Table_users::operator[](size_t index) const {
    if (index >= users.size()) {
        return nullptr;
    }
    return users[index].get();
}

ostream& operator<<(ostream& os, const Table_users& table) {
    os << "Table Users (" << table.countUsers() << " users):" << endl;
    for (size_t i = 0; i < table.users.size(); ++i) {
        os << "  " << i + 1 << ". " << *table.users[i] << endl;
    }
    return os;
}

User* Table_users::findUserByName(const string& name) const {
    auto it = find_if(users.begin(), users.end(),
        [&name](const unique_ptr<User>& user) {
            return caseInsensitiveCompare(user->getName(), name);
        });

    return (it != users.end()) ? it->get() : nullptr;
}

void Table_users::newAdvancedUser(const string& name, const string& role) {
    if (duplicateName(name)) {
        throw ExistingUserException("User had already created: " + name);
    }
    users.push_back(make_unique<AdvancedUser>(name, countUsers(), role));
}