#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {
private:
    int id;
    string name;
    int win;
    int lose;
    int allplays;
public:
    User();
    User(string name, int id_b);
    User(int id, string name, int win, int lose, int allp);
    ~User();
    int getId();
    string getName();
    int getWin();
    int getLose();
    int getAllplays();
    void userWin();
    void userLose();
    void userDeadHeat();
};

#endif