#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

// Определяем цветовые макросы как пустые строки
#define COLOR_RED ""
#define COLOR_GREEN ""
#define COLOR_DARK_GREEN ""
#define COLOR_BLUE ""
#define COLOR_CYAN ""
#define COLOR_RESET ""

// Глобальные массивы и счётчики
Car cars[MAX_CARS];
Client clients[MAX_CLIENTS];
Contract contracts[MAX_CONTRACTS];
int carCount = 0, clientCount = 0, contractCount = 0;

// Вспомогательная функция для преобразования строки в нижний регистр
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

// Сохранение данных в файлы
void saveData() {
    ofstream ofs("cars.txt");
    for (int i = 0; i < carCount; i++) {
        ofs << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " " << cars[i].color << " " << cars[i].number << " " << cars[i].price << "\n";}
    ofs.close();

    ofstream ofs2("clients.txt");
    for (int i = 0; i < clientCount; i++) {
        ofs2 << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << "\n";
    }
    ofs2.close();

    ofstream ofs3("contracts.txt");
    for (int i = 0; i < contractCount; i++) {
        ofs3 << contracts[i].name << ";" << contracts[i].surname << ";" << contracts[i].middleName << ";" << contracts[i].registrationNumber << ";" << contracts[i].carBrand << ";"<< contracts[i].carModel << ";"
    << contracts[i].rentDays << ";"<< contracts[i].startDay << ";" << contracts[i].endDay << ";" << contracts[i].totalRentalPrice << "\n";
    }
    ofs3.close();
}

// Загрузка данных из файлов
void loadData() {
    ifstream ifs("cars.txt");
    while (carCount < MAX_CARS &&
        (ifs >> cars[carCount].brand >> cars[carCount].model >> cars[carCount].year >> cars[carCount].color >> cars[carCount].number >> cars[carCount].price)) {
        carCount++;
    }
    ifs.close();

    ifstream ifs2("clients.txt");
    while (clientCount < MAX_CLIENTS &&
        (ifs2 >> clients[clientCount].name >> clients[clientCount].middle >> clients[clientCount].surname)) {
        clientCount++;
    }
    ifs2.close();

    ifstream ifs3("contracts.txt");
    string line;
    while (getline(ifs3, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        getline(ss, contracts[contractCount].name, ';');
        getline(ss, contracts[contractCount].surname, ';');
        getline(ss, contracts[contractCount].middleName, ';');
        getline(ss, contracts[contractCount].registrationNumber, ';');
        getline(ss, contracts[contractCount].carBrand, ';');
        getline(ss, contracts[contractCount].carModel, ';');
        ss >> contracts[contractCount].rentDays;
        ss.ignore();
        getline(ss, contracts[contractCount].startDay, ';');
        getline(ss, contracts[contractCount].endDay, ';');
        ss >> contracts[contractCount].totalRentalPrice;
        ss.ignore();

        contractCount++;
    }
    ifs3.close();
}

// Добавление автомобиля
void addCar() {
    if (carCount >= MAX_CARS) {
        cout << COLOR_RED << "No more cars can be added.\n" << COLOR_RESET;
        return;
    }
    Car c;
    cout << COLOR_GREEN << "Enter brand, model, year, price: " << COLOR_RESET;
    if (!(cin >> c.brand >> c.model >> c.year >> c.price)) {
        cout << COLOR_RED << "Invalid input.\n" << COLOR_RESET;
        cin.clear();
        cin.ignore(9999, '\n');
        return;
    }

    cout << COLOR_GREEN << "Available colors:\n";
    int totalColors = sizeof(colorStrings) / sizeof(colorStrings[0]);
    for (int i = 0; i < totalColors; i++) {
        cout << COLOR_GREEN << (i + 1) << ". " << colorStrings[i] << ((i + 1) % 5 == 0 ? "\n" : "\t"); // ((i + 1) % 5 == 0 ? "\n" : "\t") - это тернарный оператор, который работает следующим образом: (i + 1) % 5 == 0 проверяет, делится ли(i + 1) на 5 без остатка. Если да(т.е.это каждый пятый элемент), то добавляется символ новой строки("\n") Если нет, то добавляется табуляция("\t").
    }
    cout << "\nSelect a color (1-" << totalColors << "): " << COLOR_RESET;

    int choice;
    if (!(cin >> choice) || choice < 1 || choice > totalColors) {
        cout << COLOR_RED << "Invalid choice.\n" << COLOR_RESET;
        cin.clear();
        cin.ignore(9999, '\n');
        return;
    }
    c.color = colorStrings[choice - 1];

    cout << COLOR_GREEN << "Enter the car's number: " << COLOR_RESET;
    if (!(cin >> c.number)) {
        cout << COLOR_RED << "Invalid input.\n" << COLOR_RESET;
        cin.clear();
        cin.ignore(9999, '\n');
        return;
    }

    cars[carCount++] = c;
    cout << COLOR_GREEN << "Car added.\n" << COLOR_RESET;
    saveData();
}

// Добавление клиента
void addClient() {
    if (clientCount >= MAX_CLIENTS) {
        cout << COLOR_RED << "No more clients can be added.\n" << COLOR_RESET;
        return;
    }
    Client cl;
    cout << COLOR_GREEN << "Enter name, middle name, surname: " << COLOR_RESET;
    if (!(cin >> cl.name >> cl.middle >> cl.surname)) {
        cout << COLOR_RED << "Invalid input.\n" << COLOR_RESET;
        cin.clear();
        cin.ignore(9999, '\n');
        return;
    }
    clients[clientCount++] = cl;
    cout << COLOR_GREEN << "Client added.\n" << COLOR_RESET;
    saveData();
}

// Добавление контракта
void addContract() {
    if (contractCount >= MAX_CONTRACTS) {
        cout << COLOR_RED << "No more contracts can be added.\n" << COLOR_RESET;
        return;
    }
    Contract ct;
    cout << COLOR_GREEN << "Enter client's name, middle name, surname: " << COLOR_RESET;
    cin >> ct.name >> ct.middleName >> ct.surname;

    cout << COLOR_GREEN << "Enter registration number (15 characters max): " << COLOR_RESET;
    cin >> ct.registrationNumber;

    cout << COLOR_GREEN << "Enter car brand and model: " << COLOR_RESET;
    cin >> ct.carBrand >> ct.carModel;

    cout << COLOR_GREEN << "Enter rent days: " << COLOR_RESET;
    cin >> ct.rentDays;

    cout << COLOR_GREEN << "Enter start day (dd/mm/yyyy): " << COLOR_RESET;
    cin >> ct.startDay;

    cout << COLOR_GREEN << "Enter end day (dd/mm/yyyy): " << COLOR_RESET;
    cin >> ct.endDay;

    cout << COLOR_GREEN << "Enter total rental price: " << COLOR_RESET;
    cin >> ct.totalRentalPrice;

    contracts[contractCount++] = ct;
    cout << COLOR_GREEN << "Contract added.\n" << COLOR_RESET;
    saveData();
}

// Отображение автомобилей
void displayCars() {
    if (carCount == 0) {
        cout << COLOR_RED << "No cars to display.\n" << COLOR_RESET;
        return;
    }
    for (int i = 0; i < carCount; i++) {
        cout << COLOR_DARK_GREEN << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " " << cars[i].color << " " << cars[i].number << " " << cars[i].price << "\n" << COLOR_RESET;
    }
}

// Отображение клиентов
void displayClients() {
    if (clientCount == 0) {
        cout << COLOR_RED << "No clients to display.\n" << COLOR_RESET;
        return;
    }
    for (int i = 0; i < clientCount; i++) {
        cout << COLOR_DARK_GREEN << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << "\n" << COLOR_RESET;
    }
}

// Отображение контрактов
void displayContracts() {
    if (contractCount == 0) {
        cout << COLOR_RED << "No contracts to display.\n" << COLOR_RESET;
        return;
    }
    for (int i = 0; i < contractCount; i++) {
        cout << COLOR_DARK_GREEN << "Contract " << (i + 1) << ": "
            << contracts[i].name << " " << contracts[i].surname << " " << contracts[i].middleName << " " << contracts[i].registrationNumber << " " << contracts[i].carBrand << " " << contracts[i].carModel << " "
            << contracts[i].rentDays << " " << contracts[i].startDay << " " << contracts[i].endDay << " " << contracts[i].totalRentalPrice << "\n" << COLOR_RESET;
    }
}

// Поиск автомобиля
void searchCar() {
    int choice;
    cout << COLOR_CYAN << "Search car by: 1.Brand 2.Color 3.Number 4.Year\nChoice: " << COLOR_RESET;
    if (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << COLOR_RED << "Invalid choice.\n" << COLOR_RESET;
        cin.clear();
        cin.ignore(9999, '\n');
        return;
    }

    string key;
    int yr = 0;
    switch (choice) {
    case 1: cout << COLOR_CYAN << "Enter brand: " << COLOR_RESET; cin >> key; key = toLower(key); break;
    case 2: cout << COLOR_CYAN << "Enter color: " << COLOR_RESET; cin >> key; key = toLower(key); break;
    case 3: cout << COLOR_CYAN << "Enter number: " << COLOR_RESET; cin >> key; key = toLower(key); break;
    case 4: cout << COLOR_CYAN << "Enter year: " << COLOR_RESET; cin >> yr; break;
    }

    bool found = false;
    for (int i = 0; i < carCount; i++) {
        bool match = false;
        switch (choice) {
        case 1: match = (toLower(cars[i].brand) == key); break;
        case 2: match = (toLower(cars[i].color) == key); break;
        case 3: match = (toLower(cars[i].number) == key); break;
        case 4: match = (cars[i].year == yr); break;
        }
        if (match) {
            cout << COLOR_CYAN << "Found: " << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " " << cars[i].color << " " << cars[i].number << " " << cars[i].price << "\n" << COLOR_RESET;
            found = true;
            break;
        }
    }
    if (!found) cout << COLOR_RED << "Car not found.\n" << COLOR_RESET;
}

// Поиск клиента
void searchClient() {
    cout << COLOR_CYAN << "Enter surname: " << COLOR_RESET;
    string surname;
    cin >> surname;
    surname = toLower(surname);

    bool found = false;
    for (int i = 0; i < clientCount; i++) {
        if (toLower(clients[i].surname) == surname) {
            cout << COLOR_CYAN << "Found: " << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << "\n" << COLOR_RESET;
            found = true;
            break;
        }
    }
    if (!found) cout << COLOR_RED << "Client not found.\n" << COLOR_RESET;
}

// Поиск контракта
void searchContract() {
    cout << COLOR_CYAN << "Enter client's surname: " << COLOR_RESET;
    string surname;
    cin >> surname;
    surname = toLower(surname);

    bool found = false;
    for (int i = 0; i < contractCount; i++) {
        if (toLower(contracts[i].surname) == surname) {
            cout << COLOR_CYAN << "Found: " << contracts[i].name << " " << contracts[i].surname << " " << contracts[i].middleName << " " << contracts[i].registrationNumber << " " << contracts[i].carBrand << " " 
                << contracts[i].carModel << " " << contracts[i].rentDays << " " << contracts[i].startDay << " " << contracts[i].endDay << " " << contracts[i].totalRentalPrice << "\n" << COLOR_RESET;
            found = true;
        }
    }
    if (!found) cout << COLOR_RED << "Contract not found.\n" << COLOR_RESET;
}

// Удаление записи
void deleteEntry() {
    cout << COLOR_RED << "Delete: 1.Car 2.Client 3.Contract 4.All\nChoice: " << COLOR_RESET;
    int choice;
    if (!(cin >> choice) || choice < 1 || choice > 4) {
        cout << COLOR_RED << "Invalid choice.\n" << COLOR_RESET;
        cin.clear();
        cin.ignore(9999, '\n');
        return;
    }

    switch (choice) {
    case 1: // Удаление автомобиля
        if (carCount == 0) {
            cout << COLOR_RED << "No cars to delete.\n" << COLOR_RESET;
            return;
        }
        for (int i = 0; i < carCount; i++) {
            cout << COLOR_DARK_GREEN << "Car " << (i + 1) << ": " << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " " << cars[i].color << " " << cars[i].number << " " << cars[i].price << "\n" << COLOR_RESET;
        }
        int idx;
        cout << COLOR_RED << "Enter index to delete (1-" << carCount << "): " << COLOR_RESET;
        if (!(cin >> idx) || idx < 1 || idx > carCount) {
            cout << COLOR_RED << "Invalid choice.\n" << COLOR_RESET;
            return;
        }
        for (int i = idx - 1; i < carCount - 1; i++) cars[i] = cars[i + 1];
        carCount--;
        cout << COLOR_RED << "Car deleted.\n" << COLOR_RESET;
        saveData();
        break;

    case 2: // Удаление клиента
        if (clientCount == 0) {
            cout << COLOR_RED << "No clients to delete.\n" << COLOR_RESET;
            return;
        }
        for (int i = 0; i < clientCount; i++) {
            cout << COLOR_DARK_GREEN << "Client " << (i + 1) << ": " << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << "\n" << COLOR_RESET;
        }
        cout << COLOR_RED << "Enter index to delete (1-" << clientCount << "): " << COLOR_RESET;
        if (!(cin >> idx) || idx < 1 || idx > clientCount) {
            cout << COLOR_RED << "Invalid choice.\n" << COLOR_RESET;
            return;
        }
        for (int i = idx - 1; i < clientCount - 1; i++) clients[i] = clients[i + 1];
        clientCount--;
        cout << COLOR_RED << "Client deleted.\n" << COLOR_RESET;
        saveData();
        break;

    case 3: // Удаление контракта
        if (contractCount == 0) {
            cout << COLOR_RED << "No contracts to delete.\n" << COLOR_RESET;
            return;
        }
        for (int i = 0; i < contractCount; i++) {
            cout << COLOR_DARK_GREEN << "Contract " << (i + 1) << ": " << contracts[i].name << " " << contracts[i].surname << " " << contracts[i].middleName << " " << contracts[i].registrationNumber << " " 
                << contracts[i].carBrand << " " << contracts[i].carModel << "\n" << COLOR_RESET;
        }
        cout << COLOR_RED << "Enter index to delete (1-" << contractCount << "): " << COLOR_RESET;
        if (!(cin >> idx) || idx < 1 || idx > contractCount) {
            cout << COLOR_RED << "Invalid choice.\n" << COLOR_RESET;
            return;
        }
        for (int i = idx - 1; i < contractCount - 1; i++) contracts[i] = contracts[i + 1];
        contractCount--;
        cout << COLOR_RED << "Contract deleted.\n" << COLOR_RESET;
        saveData();
        break;

    case 4: // Удаление всех данных
        carCount = clientCount = contractCount = 0;
        cout << COLOR_RED << "All data deleted.\n" << COLOR_RESET;
        saveData();
        break;
    }
}

// Преобразование даты в количество дней
int convertToDays(const string& date) {
    int d, m, y;
    char sep1, sep2;
    istringstream iss(date);
    if (!(iss >> d >> sep1 >> m >> sep2 >> y)) return 0;
    return y * 365 + m * 30 + d;
}

// Расчёт задолженности
void calcDebt() {
    cout << COLOR_BLUE << "Enter client's surname: " << COLOR_RESET;
    string surname;
    cin.ignore();
    getline(cin, surname);
    surname = toLower(surname);

    int idx = -1;
    for (int i = 0; i < clientCount; i++) {
        if (toLower(clients[i].surname) == surname) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        cout << COLOR_RED << "Client not found.\n" << COLOR_RESET;
        return;
    }

    cout << COLOR_BLUE << "Enter today's date (dd/mm/yyyy): " << COLOR_RESET;
    string today;
    if (!(cin >> today)) {
        cout << COLOR_RED << "Invalid input.\n" << COLOR_RESET;
        cin.clear();
        cin.ignore(9999, '\n');
        return;
    }

    int diff = convertToDays(today) - convertToDays(contracts[idx].endDay);
    if (diff < 0) diff = 0;
    cout << COLOR_BLUE << "Debt for " << clients[idx].name << " " << clients[idx].surname << " is: " << diff * cars[idx].price << "\n" << COLOR_RESET;
}

#endif // FUNCTIONS_H