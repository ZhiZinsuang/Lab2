
#include <iostream>
#include <Windows.h>

#include "existingUserException.h"
#include "nonExistentUserException.h"
#include "user.h"
#include "table_users.h"
#include "play.h"
#include "table_plays.h"

using namespace std;

void testUsers() {
    cout << "1. ТЕСТ КЛАССА USER и TABLE_USERS\n";

    try {
        Table_users users("users.txt");

        // Тест 1: Добавление новых пользователей
        cout << "Добавляем пользователей...\n";
        users.newUser("Alice");
        users.newUser("Bob");
        users.newUser("Charlie");
        users.out();

        // Тест 2: Попытка дубликата
        cout << "\nПопытка добавить дубликат:\n";
        users.newUser("Alice");  // Должно выбросить исключение

    }
    catch (ExistingUserException& e) {
        cout << "✓ ОШИБКА: " << e.getMessage() << endl;
    }

    try {
        Table_users users("users.txt");
        users.out();

        // Тест 3: Получение несуществующего пользователя
        cout << "\nПопытка получить несуществующего пользователя:\n";
        //User& u = users.getUser(10);  // Должно выбросить исключение

    }
    catch (NonExistentUserException& e) {
        cout << "✓ ОШИБКА: " << e.getMessage() << endl;
    }
}

void testPlays() {
    cout << "2. ТЕСТ КЛАССА TABLE_PLAYS\n";

    Table_plays plays("plays.txt");

    // Тест 1: Добавление партий
    cout << "Добавляем партии...\n";
    plays.newPlay("Alice", "Bob");
    plays.newPlay("Charlie", "Alice");
    plays.newPlay("Bob", "Charlie");
    plays.outPlays();

    // Тест 2: Подсчет партий
    cout << "\nКоличество партий: " << plays.countPlays() << endl;

    // Тест 3: Перезапись файла и повторный вывод
    cout << "\nПосле перезаписи файла:\n";
    plays.rewrightFile();
    plays.outPlays();
}

void testIntegration() {
    cout << "3. ИНТЕГРАЦИОННЫЙ ТЕСТ\n";

    try {
        Table_users users("users.txt");
        Table_plays plays("plays.txt");

        cout << "Пользователи:\n";
        users.out();

        cout << "\nПартии:\n";
        plays.outPlays();

        // Обновляем статистику пользователей
        cout << "\nОбновляем статистику...\n";
        User* alice = users.getUser(0);
        User* bob = users.getUser(1);

        // Alice выиграла у Bob
        alice->userWin();
        bob->userLose();

        cout << "Alice: W=" << alice->getWin() << " L=" << alice->getLose()
            << " Total=" << alice->getAllplays() << endl;
        cout << "Bob: W=" << bob->getWin() << " L=" << bob->getLose()
            << " Total=" << bob->getAllplays() << endl;

    }
    catch (...) {
        ;// cout << "ОШИБКА: " << e.getMessage() << endl;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    /*Table_users n("tableUsers.txt");
    
    n.out();

    try {
        n.newUser("ho");
    }
    catch (ExistingUserException& e) {
        cout << e.getMessage() << endl;
    }
    n.out();*/

    /*Table_plays b("tablePlays.txt");
    b.newPlay("Sarina", "Goro");
    b.outPlays();*/

    cout << "=== ТЕСТИРОВАНИЕ СИСТЕМЫ ПОЛЬЗОВАТЕЛЕЙ И ПАРТИЙ ===\n\n";

    testUsers();
    cout << "\n" << string(50, '=') << "\n\n";

    testPlays();
    cout << "\n" << string(50, '=') << "\n\n";

    testIntegration();

    cout << "\n=== ВСЕ ТЕСТЫ ЗАВЕРШЕНЫ ===\n";
    
}




