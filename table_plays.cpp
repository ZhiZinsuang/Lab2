
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <algorithm>
#include "table_plays.h"
#include "falseFormatLineException.h"

using namespace std;

Table_plays::Table_plays() {}

Table_plays::Table_plays(const string& f) : file_r(f) {
    try {
        readfile();
    }
    catch (const FalseFormatLineException& e) {
        cout << e.getMessage() << endl;
    }
}

Table_plays::Table_plays(const Table_plays& other) : file_r(other.file_r) {
    // Глубокое копирование shared_ptr
    for (const auto& play : other.plays) {
        plays.push_back(make_shared<Play>(*play));
    }
}

Table_plays::~Table_plays() {
    rewrightFile();
}

void Table_plays::readfile() {
    ifstream file(file_r);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл." << endl;
        return;
    }

    try {
        string line;
        while (getline(file, line)) {
            // Используем stringstream для более безопасного парсинга
            stringstream ss(line);
            string line1, line2, line3;

            if (!(ss >> line1 >> line2 >> line3)) {
                throw FalseFormatLineException("Строка в файле неверного формата: " + line);
            }

            // Проверяем, есть ли еще данные в строке
            string extra;
            if (ss >> extra) {
                throw FalseFormatLineException("Лишние данные в строке: " + line);
            }

            plays.push_back(make_shared<Play>(stoi(line1), line2, line3));
        }
    }
    catch (const exception& e) {
        throw FalseFormatLineException(string("Ошибка чтения файла: ") + e.what());
    }

    file.close();
}

void Table_plays::outPlays() const {
    if (plays.empty()) {
        cout << "Данных нет" << endl;
    }
    else {
        for (const auto& p : plays) {
            cout << *p << endl;
        }
    }
}

void Table_plays::rewrightFile() {
    ofstream out(file_r);
    if (!out.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    for (const auto& p : plays) {
        out << p->getId() << " " << p->getUserWin() << " " << p->getUserLose() << endl;
    }

    out.close();
}

int Table_plays::countPlays() const {
    return static_cast<int>(plays.size());
}

void Table_plays::newPlay(const string& uWin, const string& uLose) {
    int id = countPlays();
    plays.push_back(make_shared<Play>(id, uWin, uLose));
}

Table_plays& Table_plays::operator=(const Table_plays& other) {
    if (this != &other) {
        file_r = other.file_r;
        plays.clear();
        for (const auto& play : other.plays) {
            plays.push_back(make_shared<Play>(*play));
        }
    }
    return *this;
}

shared_ptr<Play> Table_plays::operator[](size_t index) {
    if (index >= plays.size()) {
        throw out_of_range("Index out of range");
    }
    return plays[index];
}

const shared_ptr<Play> Table_plays::operator[](size_t index) const {
    if (index >= plays.size()) {
        throw out_of_range("Index out of range");
    }
    return plays[index];
}

ostream& operator<<(ostream& os, const Table_plays& table) {
    os << "Table Plays (" << table.countPlays() << " records):" << endl;
    for (size_t i = 0; i < table.plays.size(); ++i) {
        os << "  " << i + 1 << ". " << *table.plays[i] << endl;
    }
    return os;
}

vector<shared_ptr<Play>> Table_plays::findPlaysByPlayer(const string& playerName) const {
    vector<shared_ptr<Play>> result;

    // Поиск с использованием алгоритмов STL и лямбда-функций
    copy_if(plays.begin(), plays.end(), back_inserter(result),
        [&playerName](const shared_ptr<Play>& play) {
            // Используем find для поиска подстроки в именах игроков
            return play->getUserWin().find(playerName) != string::npos ||
                play->getUserLose().find(playerName) != string::npos;
        });

    return result;
}