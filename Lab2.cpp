
/*
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <Windows.h>

#include "Lab2.h"

using namespace std;

//выводит данные из массива в консоль
void table_users::out(){
    if (users.size() == 0)
        cout << "Данных нет" << endl;
    else {
        for (user p : users) {
            cout << p.getId() << " " << p.getName() << " " << p.getWin() << " " << p.getLose() << " " << p.getAllplays() << endl;
        }
    }
}

//считывает файл в массив vector<users>
void table_users::readfile() {
    ifstream file(file_r);
    if (!file.is_open()) 
        cout << "Не удалось открыть файл." << endl;
    else {
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
            
            users.push_back(user(stoi(line1), line2, stoi(line3), stoi(line4), stoi(line5)));
        }
    }
    file.close();
}

//проверяет, есть ли в файле такое имя
bool table_users::duplicateName(string name) {
    for (user u : users) {
        if (name == u.getName())
            return true;
    }
    return false;
}

//добавляет нового пользователя в массив
void table_users::newUser(string name) {
    if (duplicateName(name))    //проверка на повторность имени
        throw InvalidCreateUser("Такой пользователь уже есть");
    else {
        users.push_back(user(name, countUsers()));
    }
}

//возвращает кол-во пользователей
int table_users::countUsers() {
    return static_cast<int>(users.size());
}

//переписывает в файл все данные из массива
void table_users::rewrightFile() {
    ofstream out;
    out.open(file_r);
    if (out.is_open())
    {
        for (user u : users) {
            out << u.getId() << " " << u.getName() << " " << u.getWin() << " " << u.getLose() << " " << u.getAllplays() << endl;
        }
    }
    else {
        cout << "ошибка открытия файла" << endl;
    }
    out.close();
}

//возвращает пользователя с определённым индексом
user& table_users::getUser(int id) {
    return users[id];
}*/

#include <iostream>
#include <Windows.h>

#include "table_users.h"
#include "user.h"
#include "existingUserException.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Table_users n("tableUsers.txt");
    
    n.out();

    try {
        n.newUser("lo");
    }
    catch (ExistingUserException& e) {
        cout << e.getMessage() << endl;
    }

   

}

