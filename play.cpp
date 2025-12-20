#include <iostream>
#include "play.h"

using namespace std;

Play::Play(int id, string userWin, string userLose) :id(id), userWin(userWin), userLose(userLose) {}

Play::~Play() {}

int Play::getId() {
    return id;
}

string Play::getUserWin() {
    return userWin;
}

string Play::getUserLose() {
    return userLose;
}