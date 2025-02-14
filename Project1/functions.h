#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdlib>

using namespace std;

Car cars[MAX_CARS];
Client clients[MAX_CLIENTS];
int carCount = 0, clientCount = 0;

string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void saveData() {
    ofstream ofs("cars.txt");
    for (int i = 0; i < carCount; i++)
        ofs << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " " << cars[i].color << " " << cars[i].number << " " << cars[i].price << "\n";

    ofstream ofs2("clients.txt");
    for (int i = 0; i < clientCount; i++)
        ofs2 << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << " " << clients[i].rentDate << "\n";
}

void loadData() {
    ifstream ifs("cars.txt");
    carCount = 0;
    while (carCount < MAX_CARS &&
        (ifs >> cars[carCount].brand >> cars[carCount].model >> cars[carCount].year >> cars[carCount].color >> cars[carCount].number >> cars[carCount].price))
        carCount++;

    ifstream ifs2("clients.txt");
    clientCount = 0;
    while (clientCount < MAX_CLIENTS &&
        (ifs2 >> clients[clientCount].name >> clients[clientCount].middle >> clients[clientCount].surname >> clients[clientCount].rentDate))
        clientCount++;
}

void addCar() {
    if (carCount >= MAX_CARS) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    Car c;
    cout << COLOR_GREEN << "Enter the car's brand, model, and year, price: " COLOR_RESET;
    if (!(cin >> c.brand >> c.model >> c.year >> c.price)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }

    cout << COLOR_GREEN << "Available colors:\n" COLOR_RESET;
    int totalColors = sizeof(colorStrings) / sizeof(colorStrings[0]);
    for (int i = 0; i < totalColors; i++) {
        cout << COLOR_GREEN << (i + 1) << ". " << colorStrings[i];
        if ((i + 1) % 5 == 0) {
            cout << "\n";
        }
        else {
            cout << "\t";
        }
    }

    cout << COLOR_GREEN << "\nSelect a color (1-" << totalColors << "): " COLOR_RESET;
    int choice;
    if (!(cin >> choice) || choice < 1 || choice > totalColors) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    c.color = colorStrings[choice - 1];

    cout << COLOR_GREEN << "Enter the car's number: " COLOR_RESET;
    if (!(cin >> c.number)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }

    cout << COLOR_GREEN << "Enter the car's price per day: " COLOR_RESET;
    if (!(cin >> c.price)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }

    cars[carCount++] = c;
    cout << COLOR_GREEN << "Car added.\n" COLOR_RESET;
    saveData();
}

void addClient() {
    if (clientCount >= MAX_CLIENTS) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    Client cl;
    cout << COLOR_GREEN << "Enter the name, middle name, surname, and rent date (dd/mm/yyyy): " COLOR_RESET;
    if (!(cin >> cl.name >> cl.middle >> cl.surname >> cl.rentDate)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    clients[clientCount++] = cl;
    cout << COLOR_GREEN << "Client added.\n" COLOR_RESET;
    saveData(); // Save the data after adding the client
}

void displayCars() {
    if (carCount == 0) {
        cout << COLOR_RED << "No cars to display.\n" COLOR_RESET;
        return;
    }
    for (int i = 0; i < carCount; i++)
        cout << COLOR_DARK_GREEN << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " " << cars[i].color << " " << cars[i].number << " " << cars[i].price << "\n" COLOR_RESET;
}

void displayClients() {
    if (clientCount == 0) {
        cout << COLOR_RED << "No clients to display.\n" COLOR_RESET;
        return;
    }
    for (int i = 0; i < clientCount; i++)
        cout << COLOR_DARK_GREEN << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << " " << clients[i].rentDate << "\n" COLOR_RESET;
}

void searchCar() {
    int choice;
    cout << COLOR_CYAN << "Search car by: 1.Brand 2.Color 3.Number 4.Year\nChoice: " COLOR_RESET;
    if (!(cin >> choice)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    if (choice < 1 || choice > 4) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }

    string key;
    int yr = 0;
    switch (choice) {
    case 1:
        cout << COLOR_CYAN << "Enter brand: " COLOR_RESET;
        if (!(cin >> key)) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        key = toLower(key);
        break;
    case 2:
        cout << COLOR_CYAN << "Enter color: " COLOR_RESET;
        if (!(cin >> key)) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        key = toLower(key);
        break;
    case 3:
        cout << COLOR_CYAN << "Enter number: " COLOR_RESET;
        if (!(cin >> key)) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        key = toLower(key);
        break;
    case 4:
        cout << COLOR_CYAN << "Enter year: " COLOR_RESET;
        if (!(cin >> yr)) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        break;
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
            cout << COLOR_CYAN << "Found: " << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " " << cars[i].color << " " << cars[i].number << " " << cars[i].price << "\n" COLOR_RESET;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << COLOR_RED << "Car not found.\n" COLOR_RESET;
    }
}

void searchClient() {
    int choice;
    cout << COLOR_CYAN << "Search client by: 1.Surname\nChoice: " COLOR_RESET;
    if (!(cin >> choice)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    bool found = false;
    if (choice == 1) {
        string surname;
        cout << COLOR_CYAN << "Enter surname: " COLOR_RESET;
        if (!(cin >> surname)) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        surname = toLower(surname);
        for (int i = 0; i < clientCount; i++) {
            if (toLower(clients[i].surname) == surname) {
                cout << COLOR_CYAN << "Found: " << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << "\n" COLOR_RESET;
                found = true;
                break;
            }
        }
    }
    else {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    if (!found) {
        cout << COLOR_RED << "Client not found.\n" COLOR_RESET;
    }
}

// Новые функции удаления =====
void deleteCarEntry() {
    if (carCount == 0) {
        cout << COLOR_RED << "No cars to delete.\n" COLOR_RESET;
        return;
    }
    cout << COLOR_RED << "Cars:\n" COLOR_RESET;
    for (int i = 0; i < carCount; i++) {
        cout << COLOR_DARK_GREEN << "Car " << (i + 1) << ": " << cars[i].brand << " " << cars[i].model << " "
            << cars[i].year << " " << cars[i].color << " " << cars[i].number << " " << cars[i].price << "\n" COLOR_RESET;
    }
    cout << COLOR_RED << "Enter the index of the car to delete (1-" << carCount << "): " COLOR_RESET;
    int choice;
    if (!(cin >> choice) || choice < 1 || choice > carCount) {
        cout << COLOR_RED << "Invalid choice. No car deleted.\n" COLOR_RESET;
        return;
    }
    // Сдвигаем элементы влево для удаления выбранного
    for (int i = choice - 1; i < carCount - 1; i++) {
        cars[i] = cars[i + 1];
    }
    carCount--;
    cout << COLOR_RED << "Car deleted.\n" COLOR_RESET;
    saveData();
}


// Удаление клиента по выбору из списка
void deleteClientEntry() {
    if (clientCount == 0) {
        cout << COLOR_RED << "No clients to delete.\n" COLOR_RESET;
        return;
    }
    cout << COLOR_RED << "Clients:\n" COLOR_RESET;
    for (int i = 0; i < clientCount; i++) {
        cout << COLOR_DARK_GREEN << "Client " << (i + 1) << ": " << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << " " << clients[i].rentDate << "\n" COLOR_RESET;
    }
    cout << COLOR_RED << "Enter the index of the client to delete (1-" << clientCount << "): " COLOR_RESET;
    int choice;
    if (!(cin >> choice) || choice < 1 || choice > clientCount) {
        cout << COLOR_RED << "Invalid choice. No client deleted.\n" COLOR_RESET;
        return;
    }
    for (int i = choice - 1; i < clientCount - 1; i++) {
        clients[i] = clients[i + 1];
    }
    clientCount--;
    cout << COLOR_RED << "Client deleted.\n" COLOR_RESET;
    saveData();
}

// Удаление всех данных
void deleteAllData() {
    carCount = 0;
    clientCount = 0;
    cout << COLOR_RED << "All data deleted.\n" COLOR_RESET;
    saveData();
}

// Главное меню удаления
void deleteEntry() {
    int choice;
    cout << COLOR_RED << "Delete: 1. Car  2. Client  3. All\nChoice: " COLOR_RESET;
    if (!(cin >> choice)) {
        cout << COLOR_RED << "Invalid input.\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    switch (choice) {
    case 1:
        deleteCarEntry();
        break;
    case 2:
        deleteClientEntry();
        break;
    case 3:
        deleteAllData();
        break;
    default:
        cout << COLOR_RED << "Invalid choice.\n" COLOR_RESET;
        break;
    }
}

int convertToDays(const string& date) {
    int d, m, y;
    char sep1, sep2;
    istringstream iss(date);
    if (!(iss >> d >> sep1 >> m >> sep2 >> y))
        return 0;
    return y * 365 + m * 30 + d;
}

void calcDebt() {
    string surname;
    cout << COLOR_BLUE << "Enter client's surname: " COLOR_RESET;
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
        cout << COLOR_RED << "Client not found.\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    string today;
    cout << COLOR_BLUE << "Enter today's date (dd/mm/yyyy): " COLOR_RESET;
    if (!(cin >> today)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    int diff = convertToDays(today) - convertToDays(clients[idx].rentDate);
    if (diff < 0)
        diff = 0;
    cout << COLOR_BLUE << "Debt for " << clients[idx].name << " " << clients[idx].surname << " is: " << diff * cars[idx].price << "\n" COLOR_RESET;
}
#endif // FUNCTIONS_H