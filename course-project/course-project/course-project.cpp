// COURSE_PROJECT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UserManager.h"
#include "FlightManager.h"
#include "Flight.h"
#include "User.h"
#include <iostream>
#include <string>
#include <locale>
#include <windows.h>

using namespace std;

/// SAFE INPUT ///
int safeInput() {
    int value;

    try {
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            throw runtime_error("[ПОМИЛКА] Некоректно введене значення\
                                (значення має бути числовим значенням int).\n");
        }

        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        return value;
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
        return -1;
    }
}

bool checkValue(const string& input) {
    if (input.empty() && input.length() > 1) return false;

    try {
        int value = stoi(input);
        return (value >= 0 && value <= 2);
    }
    catch (const invalid_argument&) {
        return false;
    }
    catch (const out_of_range&) {
        return false;
    }
}

/// PROGRAM'S MAIN MENU ///
void mainInterface() {
    UserManager userManager("users.txt");
    FlightManager flightManager("flights.csv");
    userManager.loadFromFile();
    flightManager.loadFromFile();

    cout << "Вітаємо, користувачу!" << endl;
    while (true) {
        cout << "Будь ласка, оберіть опцію:" << endl;
        cout << "1. Увійти як адмін." << endl;
        cout << "2. Увійти як користувач." << endl;
        cout << "0. Вийти із програми." << endl;
        int input = safeInput();
        if (input == -1) {
            continue;
        }

        if (input > 2 || input < 0) {
            cout << "Помилка: Невірна опція!" << endl;
            continue;
        }

        if (input == 0) {
            cout << "До зустрічі!" << endl;
            break;
        }

        string username, password, role;
        cout << "Будь ласка, введіть логін: ";
        getline(cin, username);
        if (input == 1) cout << "Будь ласка, введіть пароль(admin123 по стандарту): ";
        else if (input == 2) cout << "Будь ласка, введіть пароль(user123 по стандарту): ";
        getline(cin, password);

        if (userManager.login(username, password, role)) {
            User user(username, password, role);
            bool session = true;
            cout << "Вхід успішний!\n" << endl;
            while (session) {
                cout << "Будь ласка, оберіть опцію: " << endl;
                int choice;
                if (role == "admin") {
                    cout << "1. Меню керування користувачами." << endl;
                    cout << "   1.1 Додати нового користувача (1)." << endl;
                    cout << "   1.2 Видалити користувача (2)." << endl;
                    cout << "   1.3 Показати список користувачів (3)." << endl;
                    cout << "   1.4 Змінити пароль (4)." << endl;
                    cout << "   1.5 Змінити ім’я користувача (5)." << endl;
                    cout << "   1.6 Показати інформацію профілю (6)." << endl;
                    cout << "2. Меню керування рейсами." << endl;
                    cout << "   2.1 Додати новий рейс (7)." << endl;
                    cout << "   2.2 Редагувати рейс (8)." << endl;
                    cout << "   2.3 Видалити рейс (9)." << endl;
                    cout << "   2.4 Показати список рейсів (10)." << endl;
                    cout << "   2.5 Пошук за одним критерієм (11)." << endl;
                    cout << "   2.6 Пошук за кількома критеріями (12)." << endl;
                    cout << "   2.7 Сортувати дані (13)." << endl;
                    cout << "   2.8 Фільтрувати дані (14)." << endl;
                    cout << "3. Довідка." << endl;
                    cout << "   3.1 Інструкція для адміністратора (15)." << endl;
                    cout << "4. Вийти (0)." << endl << endl;
                    cout << "Ваш вибір: ";
                    choice = safeInput();
                    if (choice == -1) {
                        continue;
                    }
                    switch (choice) {
                    case 1:
                        userManager.add();
                        break;
                    case 2:
                        userManager.remove();
                        break;
                    case 3:
                        userManager.showUserList();
                        break;
                    case 4:
                        user.changePassword();
                        break;
                    case 5:
                        user.changeUsername(userManager);
                        break;
                    case 6:
                        user.showProfile();
                        break;
                    case 7:
                        flightManager.add();
                        break;
                    case 8:
                        flightManager.edit();
                        break;
                    case 9:
                        flightManager.remove();
                        break;
                    case 10:
                        flightManager.showFlightList(flightManager.getFlights());
                        break;
                    case 11:
                        flightManager.search();
                        break;
                    case 12:
                        flightManager.searchMultiple();
                        break;
                    case 13:
                        flightManager.sortData();
                        break;
                    case 14:
                        flightManager.filter();
                        break;
                    case 15:
                        userManager.showAdminHelp();
                        break;
                    case 0:
                        session = false;
                        break;
                    default:
                        cout << "Помилка: Невірна опція!\n" << endl;
                        break;
                    }

                }
                if (role == "user") {
                    cout << "1. Меню рейсів." << endl;
                    cout << "   1.1 Показати всі рейси (1)." << endl;
                    cout << "   1.2 Пошук за одним критерієм (2)." << endl;
                    cout << "   1.3 Пошук за кількома критеріями (3)." << endl;
                    cout << "   1.4 Сортувати рейси (4)." << endl;
                    cout << "   1.5 Фільтрувати рейси (5)." << endl;
                    cout << "   1.6 Придбати квиток (6)." << endl;
                    cout << "2. Меню профілю." << endl;
                    cout << "   2.1 Змінити ім’я користувача (7)." << endl;
                    cout << "   2.2 Змінити пароль (8)." << endl;
                    cout << "   2.3 Показати інформацію профілю (9)." << endl;
                    cout << "   2.4 Переглянути історію посадкових талонів (10)." << endl;
                    cout << "3. Довідка." << endl;
                    cout << "   3.1 Інструкція користувача (11)." << endl;
                    cout << "4. Вийти (0)." << endl << endl;
                    cout << "Ваш вибір: ";

                    int choice = safeInput();
                    switch (choice) {
                    case 0:
                        session = false;
                        break;
                    case 1:
                        flightManager.showFlightList(flightManager.getFlights());
                        break;
                    case 2:
                        flightManager.search();
                        break;
                    case 3:
                        flightManager.searchMultiple();
                        break;
                    case 4:
                        flightManager.sortData();
                        break;
                    case 5:
                        flightManager.filter();
                        break;
                    case 6:
                        user.buyTicket(flightManager);
                        break;
                    case 7:
                        user.changeUsername(userManager);
                        break;
                    case 8:
                        user.changePassword();
                        break;
                    case 9:
                        user.showProfile();
                        break;
                    case 10:
                        user.viewBoardingPass();
                        break;
                    case 11:
                        userManager.showUserHelp();
                        break;
                    default:
                        cout << "Помилка: Невірна опція!\n" << endl;
                        break;
                    }
                }

            }
        }
        else { cout << "Помилка: невірний логін чи пароль.\n" << endl; }

    }
    return;
}

int main()
{
    setlocale(LC_ALL, "ukr");
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    mainInterface();
}