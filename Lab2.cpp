
#include <iostream>
#include <Windows.h>
#include <memory>
#include <vector>
#include "table_users.h"
#include "table_plays.h"
#include "existingUserException.h"
#include "nonExistentUserException.h"
#include "cloneable.h"

using namespace std;

// Демонстрация виртуальных функций
void demonstratePolymorphism() {
    cout << "\n=== Демонстрация полиморфизма ===" << endl;

    // Создание объектов
    User baseUser("BasePlayer", 1);
    AdvancedUser advancedUser("AdvancedPlayer", 2, "Admin");

    // Вызов через невиртуальную функцию
    cout << "\nВызов через невиртуальную функцию:" << endl;
    baseUser.showPlayerType();
    advancedUser.showPlayerType();

    // Демонстрация через указатели базового класса
    cout << "\nДемонстрация через указатели:" << endl;
    vector<User*> players;
    players.push_back(&baseUser);
    players.push_back(&advancedUser);

    for (auto player : players) {
        cout << "Type: " << player->getType() << endl;
        player->displayInfo();
        cout << endl;
    }

    // Демонстрация разницы при НЕвиртуальной функции
    cout << "\nЕсли бы getType() не был виртуальным:" << endl;
    cout << "Все объекты показали бы 'Base User'" << endl;
}

// Демонстрация клонирования
void demonstrateCloning() {
    cout << "\n=== Демонстрация клонирования ===" << endl;

    int scores[] = { 85, 90, 78 };
    CloneablePlayer original("OriginalPlayer", scores, 3);

    cout << "Original: ";
    original.display();

    // Поверхностное копирование (опасно!)
    CloneablePlayer shallowCopy = original;
    cout << "Shallow copy: ";
    shallowCopy.display();

    // Изменяем original
    original.addScore(95);

    cout << "\nПосле изменения original:" << endl;
    cout << "Original: ";
    original.display();
    cout << "Shallow copy: ";
    shallowCopy.display();
    cout << "Проблема: shallow copy имеет dangling pointer!" << endl;

    // Глубокое копирование
    CloneablePlayer* deepCopy = original.deepCopy();
    cout << "\nDeep copy: ";
    deepCopy->display();

    delete deepCopy;
}

// Демонстрация абстрактного класса
void demonstrateAbstractClass() {
    cout << "\n=== Демонстрация абстрактного класса ===" << endl;

    // Нельзя создать экземпляр абстрактного класса
    // PlayerBase abstractPlayer("Abstract"); // Ошибка компиляции!

    // Но можно использовать указатели
    vector<unique_ptr<PlayerBase>> playerList;
    playerList.push_back(make_unique<User>("User1", 1));
    playerList.push_back(make_unique<AdvancedUser>("User2", 2, "Moderator"));

    for (const auto& player : playerList) {
        cout << "Player type: " << player->getType() << endl;
    }
}

// Демонстрация присваивания
void demonstrateAssignment() {
    cout << "\n=== Демонстрация присваивания ===" << endl;

    User baseUser("Base", 10);
    AdvancedUser advancedUser("Advanced", 20, "Admin");

    cout << "Before assignment:" << endl;
    cout << "Advanced user role: " << advancedUser.getRole() << endl;

    // Присваивание объекта базового класса производному
    advancedUser = baseUser;

    cout << "After assignment from base to derived:" << endl;
    cout << "Advanced user type: " << advancedUser.getType() << endl;
    cout << "Role reset to: " << advancedUser.getRole() << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    try {
        // Существующий код
        auto userPtr = make_shared<User>("John", 1);
        cout << *userPtr << endl;

        Table_users users("users.txt");
        users.newUser("Alice");
        users.newUser("Bob");
        users.newAdvancedUser("Charlie", "Admin");

        // Новые демонстрации
        demonstratePolymorphism();
        demonstrateCloning();
        demonstrateAbstractClass();
        demonstrateAssignment();

        // Демонстрация запрета копирования
        cout << "\n=== Демонстрация запрета копирования ===" << endl;
        cout << "GameLogger использует удаленные конструкторы копирования" << endl;
        cout << "GameLogger logger2 = logger1; // Ошибка компиляции" << endl;

        // Демонстрация виртуального деструктора
        cout << "\n=== Демонстрация виртуального деструктора ===" << endl;
        {
            PlayerBase* player = new AdvancedUser("Temp", 99, "Tester");
            cout << "Creating polymorphic object..." << endl;
            delete player; // Вызовется правильный деструктор
            cout << "Если деструктор не виртуальный, вызвался бы только ~PlayerBase()" << endl;
        }

    }
    catch (const ExistingUserException& e) {
        cerr << "Error: " << e.getMessage() << endl;
    }
    catch (const NonExistentUserException& e) {
        cerr << "Error: " << e.getMessage() << endl;
    }
    catch (const exception& e) {
        cerr << "Unexpected error: " << e.what() << endl;
    }

    return 0;
}