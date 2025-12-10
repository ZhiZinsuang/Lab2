
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class users {
public:
    string name;
    int win;
    int lose;
    int allplays;
public:
    users() : name("player"), win(0), lose(0), allplays(0) {}
    users(string name, int win, int lose, int allp) : name(name), win(win), lose(lose), allplays(allp) {}
    ~users() {}
};

class table_users {
public:
    string file_r;
public:
    table_users() {}
    table_users(string f) : file_r(f) {}
    void outTable();
    void out(vector<users>& people);
    vector<users> readfile();
};

void table_users::out(vector<users>& people){
    for (const auto& p : people) {
        cout << p.name << endl;
    }
}

void table_users::outTable() {
    vector<users> list;

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

            list.push_back(users(line1, stoi(line2), stoi(line3), stoi(line4)));
        }
    }
    file.close();

    // печать
    for (const auto& p : list) {
        cout << p.name << endl;
    }
}

vector<users> table_users::readfile() {
    vector<users> list;

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
            
            list.push_back(users(line1, stoi(line2), stoi(line3), stoi(line4)));
        }
    }
    file.close();
    return list;
}

int main()
{
    vector<users> list;
    table_users n("tableUsers.txt");
    //n.outTable();
    list=n.readfile();
    n.out(list);

}

