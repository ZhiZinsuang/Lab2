
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

class users {
private:
    string name;
    int win;
    int lose;
    int allplays;
public:
    users() : name("player"), win(0), lose(0), allplays(0) {}
    users(string name, int win, int lose, int allp) : name(name), win(win), lose(lose), allplays(allp) {}
    ~users() {}
    string getName() { return name; }
};

class table_users {
private:
    string file_r;
    vector<users> usersmas;
public:
    table_users() {}
    table_users(string f) : file_r(f) {}
    void out();
    void readfile();
};

void table_users::out(){
    for (users p : usersmas) {
        cout << p.getName() << endl;
    }
}

void table_users::readfile() {
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
            
            usersmas.push_back(users(line1, stoi(line2), stoi(line3), stoi(line4)));
        }
    }
    file.close();
}

int main()
{
    table_users n("tableUsers.txt");
    //n.outTable();
    n.readfile();
    n.out();

}

