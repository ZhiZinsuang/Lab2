
#ifndef TABLE_USERS_H
#define TABLE_USERS_H

#include <iostream>
#include <vector>
#include <exception>
#include <string>

using namespace std;

class user {
private:
    int id;
    string name;
    int win;
    int lose;
    int allplays;
public:
    user() : id(0), name("player"), win(0), lose(0), allplays(0) {}
    user(string name, int id_b) : id(0), name(name), win(0), lose(0), allplays(0) {
        if (id_b != 0)
            id = id_b + 1;
    }
    user(int id, string name, int win, int lose, int allp) : id(id), name(name), win(win), lose(lose), allplays(allp) {}
    ~user() {}
    int getId() { return id; }
    string getName() { return name; }
    int getWin() { return win; }
    int getLose() { return lose; }
    int getAllplays() { return allplays; }
};

class table_users {
private:
    string file_r;
    vector<user> users;
public:
    table_users() {}
    table_users(string f) : file_r(f) {
        readfile();
    }
    ~table_users() {
        rewrightFile();
    }
    void out();     //вывод из массива в консоль
    void readfile();    //чтение данных из файла в vector<users>
    void newUser(string name);      //записывает нового пользователя в массив
    bool duplicateName(string name);     //проверяет, есть ли уже пользователь с таким именем
    int countUsers();       //возвращает кол-во пользователей в массиве
    void rewrightFile();    //переписывает в файл все данные из массива
    user getUser(int id);   //возвращает пользователя с определённым индексом
};

class InvalidCreateUser : public exception {
private:
    string message;
public:
    InvalidCreateUser(const string& message) :message(message) {}
    string getMessage() { return message; }
};

#endif 