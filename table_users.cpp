#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "table_users.h"
#include "existingUserException.h"
#include "falseFormatLineException.h"

using namespace std;

Table_users::Table_users() {}

Table_users::Table_users(string f) : file_r(f) {
    try {
        readfile();
    }
    catch (FalseFormatLineException& e) {
        cout << e.getMessage() << endl;
    }  
}

Table_users::~Table_users() {
    rewrightFile();
}

//выводит данные из массива в консоль
void Table_users::out() {
    if (users.size() == 0)
        cout << "Данных нет" << endl;
    else {
        for (User p : users) {
            cout << p.getId() << " " << p.getName() << " " << p.getWin() << " " << p.getLose() << " " << p.getAllplays() << endl;
        }
    }
}

//считывает файл в массив vector<users>
void Table_users::readfile() {
    ifstream file(file_r);
    if (!file.is_open())
        cout << "Не удалось открыть файл." << endl;
    else {
        try {
            string line;
            string line1, line2, line3, line4, line5;
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
                    else if (i == 2)
                        line3 = line.substr(start, end - start);
                    else if (i == 3)
                        line4 = line.substr(start, end - start);
                    start = end + 1;
                    end = line.find(delimiter, start);
                    i++;
                }
                line5 = line.substr(start);

                users.push_back(User(stoi(line1), line2, stoi(line3), stoi(line4), stoi(line5)));
            }
        }catch (...) {
            throw FalseFormatLineException("Строка в файле неверного формата");
        }
        
    }
    file.close();
}

//проверяет, есть ли в файле такое имя
bool Table_users::duplicateName(string name) {
    for (User u : users) {
        if (name == u.getName())
            return true;
    }
    return false;
}

//добавляет нового пользователя в массив
void Table_users::newUser(string name) {
    if (duplicateName(name))    //проверка на повторность имени
        throw ExistingUserException("User had already created");
    else {
        users.push_back(User(name, countUsers()));
    }
}

//возвращает кол-во пользователей
int Table_users::countUsers() {
    return static_cast<int>(users.size());
}

//переписывает в файл все данные из массива
void Table_users::rewrightFile() {
    ofstream out;
    out.open(file_r);
    if (out.is_open())
    {
        for (User u : users) {
            out << u.getId() << " " << u.getName() << " " << u.getWin() << " " << u.getLose() << " " << u.getAllplays() << endl;
        }
    }
    else {
        cout << "ошибка открытия файла" << endl;
    }
    out.close();
}

//возвращает пользователя с определённым индексом
User& Table_users::getUser(int id) {
    return users[id];
}