#ifndef PLAY_H
#define PLAY_H

#include <iostream>

using namespace std;

class Play {
private:
    int id;
    string userWin;
    string userLose;
public:
    Play(int id, string userWin, string userLose);
    ~Play();
    int getId();
    string getUserWin();
    string getUserLose();
};

#endif