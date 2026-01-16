
#ifndef CLONEABLE_H
#define CLONEABLE_H

#include <memory>
#include <iostream>

class CloneablePlayer {
protected:
    std::string name;
    int* scores; // Динамический массив для демонстрации глубокого копирования
    int scoreCount;

public:
    CloneablePlayer(const std::string& name, const int* scores = nullptr, int count = 0)
        : name(name), scoreCount(count) {
        if (count > 0 && scores) {
            this->scores = new int[count];
            for (int i = 0; i < count; i++) {
                this->scores[i] = scores[i];
            }
        }
        else {
            this->scores = nullptr;
        }
    }

    virtual ~CloneablePlayer() {
        delete[] scores;
    }

    // Поверхностное копирование (по умолчанию)
    CloneablePlayer(const CloneablePlayer& other)
        : name(other.name), scores(other.scores), scoreCount(other.scoreCount) {
        std::cout << "Shallow copy constructor called" << std::endl;
    }

    // Глубокое копирование
    CloneablePlayer* deepCopy() const {
        auto copy = new CloneablePlayer(name);
        if (scoreCount > 0) {
            copy->scores = new int[scoreCount];
            copy->scoreCount = scoreCount;
            for (int i = 0; i < scoreCount; i++) {
                copy->scores[i] = scores[i];
            }
        }
        return copy;
    }

    void addScore(int score) {
        // Реаллокация массива
        int* newScores = new int[scoreCount + 1];
        for (int i = 0; i < scoreCount; i++) {
            newScores[i] = scores[i];
        }
        newScores[scoreCount] = score;

        delete[] scores;
        scores = newScores;
        scoreCount++;
    }

    void display() const {
        std::cout << "Player: " << name << ", Scores: ";
        if (scores) {
            for (int i = 0; i < scoreCount; i++) {
                std::cout << scores[i] << " ";
            }
        }
        std::cout << std::endl;
    }
};

#endif