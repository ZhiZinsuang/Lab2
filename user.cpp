
#include <iostream>
#include "user.h"

using namespace std;

User::User() : id(0), name("player"), win(0), lose(0), allplays(0) {}

User::User(string name, int id_b) : id(0), name(name), win(0), lose(0), allplays(0) {
    if (id_b != 0)
        id = id_b + 1;
}

User::User(int id, string name, int win, int lose, int allp) : id(id), name(name), win(win), lose(lose), allplays(allp) {}
User::~User() {}

int User::getId() { 
    return id; 
}

string User::getName() {
    return name; 
}

int User::getWin() { 
    return win; 
}

int User::getLose() { 
    return lose; 
}

int User::getAllplays() { 
    return allplays; 
}

void User::userWin() {
    win++;
    allplays++;
}

void User::userLose() {
    lose++;
    allplays++;
}

void User::userDeadHeat() {
    allplays++;
}