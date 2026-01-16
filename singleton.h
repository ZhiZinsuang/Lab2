
#ifndef SINGLETON_H
#define SINGLETON_H

#include <string>
#include <memory>

class GameLogger {
private:
    static std::unique_ptr<GameLogger> instance;
    std::string logFile;

    GameLogger(const std::string& file) : logFile(file) {}

    // Запрещаем копирование и присваивание
    GameLogger(const GameLogger&) = delete;
    GameLogger& operator=(const GameLogger&) = delete;

public:
    static GameLogger& getInstance(const std::string& file = "game.log") {
        if (!instance) {
            instance.reset(new GameLogger(file));
        }
        return *instance;
    }

    void log(const std::string& message) {
        // Логирование в файл
    }

    std::string getLogFile() const { return logFile; }
};

#endif