#ifndef TABLE_PLAYS_H
#define TABLE_PLAYS_H

#include <iostream>
#include <vector>

#include "play.h"

using namespace std;

class Table_plays {
private:
    string file_r;
    vector<Play> plays;
public:
    Table_plays();
    Table_plays(string f);
    ~Table_plays();
    void outPlays();
    void readfile();
    void rewrightFile();
    int countPlays();
    void newPlay(string uWin, string uLose);
};

#endif