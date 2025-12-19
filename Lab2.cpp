
#include <iostream>

#include <Windows.h>

#include "existingUserException.h"
#include "user.h"
#include "table_users.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Table_users n("tableUsers.txt");

    User* nu = new User();
    nu = n.getUser(1);
    cout << nu->getName() << endl;
    
    n.out();

    try {
        n.newUser("lo");
    }
    catch (ExistingUserException& e) {
        cout << e.getMessage() << endl;
    }
    delete nu;
}

