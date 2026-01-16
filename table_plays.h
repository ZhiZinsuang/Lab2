
#ifndef TABLE_PLAYS_H
#define TABLE_PLAYS_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "play.h"

class Table_plays {
private:
    std::string file_r;
    std::vector<std::shared_ptr<Play>> plays; // Используем shared_ptr
public:
    Table_plays();
    Table_plays(const std::string& f);
    Table_plays(const Table_plays& other); // Конструктор копирования
    ~Table_plays();

    void outPlays() const;
    void readfile();
    void rewrightFile();
    int countPlays() const;
    void newPlay(const std::string& uWin, const std::string& uLose);

    // Перегрузка операторов
    Table_plays& operator=(const Table_plays& other);
    std::shared_ptr<Play> operator[](size_t index);
    const std::shared_ptr<Play> operator[](size_t index) const;
    friend std::ostream& operator<<(std::ostream& os, const Table_plays& table);

    // Поиск по имени игрока
    std::vector<std::shared_ptr<Play>> findPlaysByPlayer(const std::string& playerName) const;
};

#endif