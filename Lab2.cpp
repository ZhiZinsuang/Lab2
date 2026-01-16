// main.cpp (пример использования)
#include <iostream>
#include <memory>
#include "table_users.h"
#include "table_plays.h"
#include "existingUserException.h"
#include "nonExistentUserException.h"

using namespace std;

int main() {
    try {
        // Пример работы с умными указателями
        {
            auto userPtr = make_shared<User>("John", 1);
            cout << *userPtr << endl;

            auto playPtr = make_unique<Play>(1, "John", "Alice");
            cout << *playPtr << endl;
        }

        // Пример работы с Table_users
        Table_users users("users.txt");

        // Добавление пользователей
        users.newUser("Alice");
        users.newUser("Bob");
        users.newAdvancedUser("Charlie", "Admin");

        // Поиск пользователя
        User* foundUser = users.findUserByName("alice"); // регистронезависимый поиск
        if (foundUser) {
            cout << "Found: " << *foundUser << endl;
        }

        // Использование перегруженных операторов
        cout << users << endl;

        // Пример работы с Table_plays
        Table_plays plays("plays.txt");
        plays.newPlay("Alice", "Bob");
        plays.newPlay("Charlie", "Alice");

        // Поиск игр по игроку
        auto alicePlays = plays.findPlaysByPlayer("Alice");
        cout << "Alice's plays: " << alicePlays.size() << endl;

        // Использование перегруженных операторов
        cout << plays << endl;

        // Пример конкатенации строк
        if (!alicePlays.empty()) {
            cout << combinePlayInfo(*alicePlays[0]) << endl;
        }

        // Пример форматированного вывода
        if (foundUser) {
            cout << formatUserStats(*foundUser) << endl;
        }

        // Пример работы с конструктором копирования
        Table_users usersCopy(users);
        cout << "Copied table has " << usersCopy.countUsers() << " users" << endl;

        // Пример работы с наследованием
        AdvancedUser admin("Admin", 99, "SuperAdmin");
        cout << admin.getType() << endl;

    }
    catch (ExistingUserException& e) {
        cerr << "Error: " << e.getMessage() << endl;
    }
    catch (NonExistentUserException& e) {
        cerr << "Error: " << e.getMessage() << endl;
    }
    catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }

    return 0;
}