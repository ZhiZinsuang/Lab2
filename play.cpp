
#include <iostream>
#include <sstream>
#include "play.h"

using namespace std;

Play::Play(int id, const string& userWin, const string& userLose)
    : id(id), userWin(userWin), userLose(userLose) {}

Play::Play(const Play& other)
    : id(other.id), userWin(other.userWin), userLose(other.userLose) {}

Play::~Play() {}

int Play::getId() const {
    return id;
}

string Play::getUserWin() const {
    return userWin;
}

string Play::getUserLose() const {
    return userLose;
}

// Перегрузка оператора присваивания
Play& Play::operator=(const Play& other) {
    if (this != &other) {
        id = other.id;
        userWin = other.userWin;
        userLose = other.userLose;
    }
    return *this;
}

bool Play::operator==(const Play& other) const {
    return id == other.id &&
        userWin == other.userWin &&
        userLose == other.userLose;
}

bool Play::operator!=(const Play& other) const {
    return !(*this == other);
}

ostream& operator<<(ostream& os, const Play& play) {
    os << "Play ID: " << play.id
        << ", Winner: " << play.userWin
        << ", Loser: " << play.userLose;
    return os;
}

string combinePlayInfo(const Play& play) {
    return "Match #" + to_string(play.id) + ": " +
        play.userWin + " vs " + play.userLose;
}