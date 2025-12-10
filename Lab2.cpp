
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class names {
public:
    string name;
    int win;
    int lose;
    int allplays;
public:
    names() : name("player"), win(0), lose(0), allplays(0) {}
    names(string name, int win, int lose, int allp) : name(name), win(win), lose(lose), allplays(allp) {}
    ~names() {}
};

class table_names {
public:
    string file_r;
public:
    table_names() {}
    table_names(string f) : file_r(f) {}
    void outTable();
    vector<names>& readfile();
};

void table_names::outTable() {
    vector<names> list;

    ifstream file(file_r);
    if (!file.is_open())
        cout << "Не удалось открыть файл." << endl;
    else {
        string line;
        string line1, line2, line3, line4;
        while (std::getline(file, line)) {
            int i = 0;
            char delimiter = ' ';
            size_t start = 0;
            size_t end = line.find(delimiter);
            while (end != string::npos) {
                if (i == 0)
                    line1 = line.substr(start, end - start);
                else if (i == 1)
                    line2 = line.substr(start, end - start);
                else if (i == 2)
                    line3 = line.substr(start, end - start);
                start = end + 1;
                end = line.find(delimiter, start);
                i++;
            }
            line4 = line.substr(start);

            list.push_back(names(line1, stoi(line2), stoi(line3), stoi(line4)));
        }
    }
    file.close();

    // печать
    for (const auto& p : list) {
        cout << p.name << endl;
    }
}

vector<names>& table_names::readfile() {
    vector<names> list;

    ifstream file(file_r);
    if (!file.is_open()) 
        cout << "Не удалось открыть файл." << endl;
    else {
        string line;
        while (std::getline(file, line)) {
            //cout << line << endl;

            string line1, line2, line3, line4;
            int i = 0;
            char delimiter = ' ';
            size_t start = 0;
            size_t end = line.find(delimiter);
            while (end != string::npos) {
                if (i == 0)
                    line1 = line.substr(start, end - start);
                else if (i == 1)
                    line2 = line.substr(start, end - start);
                else if (i == 2)
                    line3 = line.substr(start, end - start);
                //std::cout << line.substr(start, end - start) << std::endl;
                start = end + 1;
                end = line.find(delimiter, start);
                i++;
            }
            line4 = line.substr(start);
            //std::cout << line.substr(start) << std::endl; // Последняя часть
            
            list.push_back(names(line1, stoi(line2), stoi(line3), stoi(line4)));
            
        }
    }
    file.close();
    return list;
}

int main()
{
    table_names n("tableNames.txt");
    n.outTable();
}

