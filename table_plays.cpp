#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <string>

#include "table_plays.h"
#include "falseFormatLineException.h"
#include "nonExistentUserException.h"

using namespace std;

Table_plays::Table_plays() {}

Table_plays::~Table_plays() {
    rewrightFile();
}

Table_plays::Table_plays(string f) : file_r(f) {
    try { 
        readfile(); 
    }
    catch (FalseFormatLineException& e) {
        cout << e.getMessage() << endl;
    }
}

void Table_plays::readfile() {
    ifstream file(file_r);
    if (!file.is_open())
        cout << "Не удалось открыть файл." << endl;
    else {
        try {
            string line;
            string line1, line2, line3;
            while (getline(file, line)) {
                int i = 0;
                char delimiter = ' ';
                size_t start = 0;
                size_t end = line.find(delimiter);
                while (end != string::npos) {
                    if (i == 0)
                        line1 = line.substr(start, end - start);
                    else if (i == 1)
                        line2 = line.substr(start, end - start);
                    start = end + 1;
                    end = line.find(delimiter, start);
                    i++;
                }
                line3 = line.substr(start);

                plays.push_back(Play(stoi(line1), line2, line3));
            }
        }catch (...) {
            throw FalseFormatLineException("Строка в файле неверного формата");
        }
    }
    file.close();
}

void Table_plays::outPlays() {
    if (plays.size() == 0)
        cout << "Данных нет" << endl;
    else {
        for (Play p : plays) {
            cout << p.getId() << " " << p.getUserWin() << " " << p.getUserLose() << endl;
        }
    }
}

void Table_plays::rewrightFile() {
    ofstream out;
    out.open(file_r);
    if (out.is_open())
    {
        for (Play p : plays) {
            out << p.getId() << " " << p.getUserWin() << " " << p.getUserLose() << endl;
        }
    }
    else {
        cout << "ошибка открытия файла" << endl;
    }
    out.close();
}

int Table_plays::countPlays() {
    return static_cast<int>(plays.size());
}

 shared_ptr<User> Table_plays::getUserByName(Table_users& usersTable, string& name) const {
     for (int i = 0; i < usersTable.countUsers(); ++i) {
         auto user = usersTable.getUser(i);
         if (user->getName() == name) {
             return user;  // Возвращаем найденного пользователя
         }
     }
     throw NonExistentUserException("Пользователь '" + name + "' не найден");
 }

 void Table_plays::newPlay(string uWin, string uLose, Table_users& usersTable) {
     int id = countPlays();
     plays.emplace_back(id, uWin, uLose);  // Добавляем игру

     try {
         // Находим победителя и обновляем статистику
         //const auto& user1 = getUserByName(usersTable, uWin);  // Ссылка на возвращаемый shared_ptr
         //user1->userWin();
         auto user1 = getUserByName(usersTable, uWin);  // Ссылка на возвращаемый shared_ptr
         user1->userWin();

         // Находим проигравшего и обновляем статистику  
         //const auto& user2 = getUserByName(usersTable, uLose);
         //user2->userLose(); // userLose() вызывается на КОПИИ!
     }
     catch (NonExistentUserException& e) {
         cout << "Ошибка: " << e.getMessage() << endl;
         // Откатываем добавление игры при ошибке
         plays.pop_back();
     }
 }