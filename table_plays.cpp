#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include "table_plays.h"
#include "falseFormatLineException.h"

using namespace std;

Table_plays::Table_plays() {}

Table_plays::~Table_plays() {
    rewrightFile();
}

Table_plays::Table_plays(string f) : file_r(f) {
    try { 
        readfile(); 
    }
    catch (FalseFormatLineException& e) {
        cout << e.getMessage() << endl;
    }
}

void Table_plays::readfile() {
    ifstream file(file_r);
    if (!file.is_open())
        cout << "Не удалось открыть файл." << endl;
    else {
        try {
            string line;
            string line1, line2, line3;
            while (getline(file, line)) {
                int i = 0;
                char delimiter = ' ';
                size_t start = 0;
                size_t end = line.find(delimiter);
                while (end != string::npos) {
                    if (i == 0)
                        line1 = line.substr(start, end - start);
                    else if (i == 1)
                        line2 = line.substr(start, end - start);
                    start = end + 1;
                    end = line.find(delimiter, start);
                    i++;
                }
                line3 = line.substr(start);

                plays.push_back(Play(stoi(line1), line2, line3));
            }
        }catch (...) {
            throw FalseFormatLineException("Строка в файле неверного формата");
        }
    }
    file.close();
}

void Table_plays::outPlays() {
    if (plays.size() == 0)
        cout << "Данных нет" << endl;
    else {
        for (Play p : plays) {
            cout << p.getId() << " " << p.getUserWin() << " " << p.getUserLose() << endl;
        }
    }
}

void Table_plays::rewrightFile() {
    ofstream out;
    out.open(file_r);
    if (out.is_open())
    {
        for (Play p : plays) {
            out << p.getId() << " " << p.getUserWin() << " " << p.getUserLose() << endl;
        }
    }
    else {
        cout << "ошибка открытия файла" << endl;
    }
    out.close();
}

int Table_plays::countPlays() {
    return static_cast<int>(plays.size());
}

void Table_plays::newPlay(string uWin, string uLose) {
    int id = countPlays();
    plays.push_back(Play(id, uWin, uLose));
}
