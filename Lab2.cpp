
#include <iostream>
#include <Windows.h>

#include "existingUserException.h"
#include "user.h"
#include "table_users.h"
#include "play.h"
#include "table_plays.h"

using namespace std;



int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    /*Table_users n("tableUsers.txt");
    
    n.out();

    try {
        n.newUser("lo");
    }
    catch (ExistingUserException& e) {
        cout << e.getMessage() << endl;
    }*/

    Table_plays b("tablePlays.txt");
    b.newPlay("Sarina", "Goro");
    b.outPlays();
}

