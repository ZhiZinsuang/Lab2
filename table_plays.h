#ifndef TABLE_PLAYS_H
#define TABLE_PLAYS_H

#include <iostream>
#include <vector>
#include <memory>

#include "play.h"
#include "table_users.h"

using namespace std;

class Table_plays {
private:
    string file_r;
    vector<Play> plays;
    shared_ptr<User> getUserByName(Table_users& usersTable, string& name) const;
public:
    Table_plays();
    Table_plays(string f);
    ~Table_plays();
    void outPlays();
    void readfile();
    void rewrightFile();
    int countPlays();
    void newPlay(string uWin, string uLose, Table_users& usersTable);
};

#endif