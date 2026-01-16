
#ifndef PLAY_H
#define PLAY_H

#include <iostream>
#include <string>
#include <memory>

class Play {
private:
    int id;
    std::string userWin;
    std::string userLose;
public:
    Play(int id, const std::string& userWin, const std::string& userLose);
    Play(const Play& other); // Конструктор копирования
    ~Play();

    int getId() const;
    std::string getUserWin() const;
    std::string getUserLose() const;

    // Перегрузка операторов
    Play& operator=(const Play& other);
    bool operator==(const Play& other) const;
    bool operator!=(const Play& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Play& play);

    // Дружественная функция для конкатенации информации
    friend std::string combinePlayInfo(const Play& play);
};

#endif