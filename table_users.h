#ifndef TABLE_USERS_H
#define TABLE_USERS_H

#include <iostream>
#include <vector>

#include "user.h"

using namespace std;

class Table_users {
private:
    string file_r;
    vector<User*> users;
public:
    Table_users();
    Table_users(string f);
    ~Table_users();
    void out();     //вывод из массива в консоль
    void readfile();    //чтение данных из файла в vector<users>
    void newUser(string name);      //записывает нового пользователя в массив
    bool duplicateName(string name);     //проверяет, есть ли уже пользователь с таким именем
    int countUsers();       //возвращает кол-во пользователей в массиве
    void rewrightFile();    //переписывает в файл все данные из массива
    User* getUser(int id);   //возвращает пользователя с определённым индексом
};

#endif
