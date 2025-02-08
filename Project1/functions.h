#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "data.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm> // Для std::transform
#include <cstdlib>   // Для exit()

using namespace std;

Car cars[MAX_CARS];
Client clients[MAX_CLIENTS];
int carCount = 0, clientCount = 0;

string colors[MAX_COLORS];
int colorCount = 0;

// Вспомогательная функция для перевода строки в нижний регистр
string toLower(string str) {
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

void saveData() {
    ofstream ofs("cars.txt");
    for (int i = 0; i < carCount; i++)
        ofs << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " "
        << cars[i].color << " " << cars[i].number << "\n";

    ofstream ofs2("clients.txt");
    for (int i = 0; i < clientCount; i++)
        ofs2 << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << " "
        << clients[i].rentDate << " " << clients[i].price << "\n";
}

void loadData() {
    ifstream ifs("cars.txt");
    carCount = 0;
    while (carCount < MAX_CARS && (ifs >> cars[carCount].brand >> cars[carCount].model
        >> cars[carCount].year >> cars[carCount].color >> cars[carCount].number))
        carCount++;

    ifstream ifs2("clients.txt");
    clientCount = 0;
    while (clientCount < MAX_CLIENTS && (ifs2 >> clients[clientCount].name >> clients[clientCount].middle
        >> clients[clientCount].surname >> clients[clientCount].rentDate >> clients[clientCount].price))
        clientCount++;

    ifstream ifs3("color.txt");
    colorCount = 0;
    while (colorCount < MAX_COLORS && getline(ifs3, colors[colorCount]))
        colorCount++;
}

void addCar() {
    if (carCount >= MAX_CARS) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    if (colorCount == 0) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    Car c;
    cout << "Enter the car's brand, model, and year: ";
    if (!(cin >> c.brand >> c.model >> c.year)) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }

    cout << "Available colors:\n";
    for (int i = 0; i < colorCount; i++)
        cout << i + 1 << ". " << colors[i] << "  ";
    cout << "\nSelect a color (1-" << colorCount << "): ";

    int choice;
    if (!(cin >> choice)) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    if (choice < 1 || choice > colorCount) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    // Индексация с 0: при выборе 1 выбирается colors[0]
    c.color = colors[choice - 1];

    cout << "Enter the car's number: ";
    if (!(cin >> c.number)) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    cars[carCount++] = c;
    cout << "Car added.\n";
}

void addClient() {
    if (clientCount >= MAX_CLIENTS) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    Client cl;
    cout << "Enter the name, middle name, surname, rent date (dd/mm/yyyy), and price per day: ";
    if (!(cin >> cl.name >> cl.middle >> cl.surname >> cl.rentDate >> cl.price)) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    clients[clientCount++] = cl;
    cout << "Client added.\n";
}

void displayCars() {
    if (carCount == 0) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < carCount; i++)
        cout << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " "
        << cars[i].color << " " << cars[i].number << "\n";
}

void displayClients() {
    if (clientCount == 0) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < clientCount; i++)
        cout << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << " "
        << clients[i].rentDate << " " << clients[i].price << "\n";
}

void searchCar() {
    int choice;
    cout << "Search car by: 1.Brand 2.Color 3.Number 4.Year\nChoice: ";
    if (!(cin >> choice)) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    if (choice < 1 || choice > 4) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }

    string key;
    int yr = 0;
    switch (choice) {
    case 1:
        cout << "Enter brand: ";
        if (!(cin >> key)) {
            cout << "некорректное значение\n";
            exit(EXIT_FAILURE);
        }
        key = toLower(key);
        break;
    case 2:
        cout << "Enter color: ";
        if (!(cin >> key)) {
            cout << "некорректное значение\n";
            exit(EXIT_FAILURE);
        }
        key = toLower(key);
        break;
    case 3:
        cout << "Enter number: ";
        if (!(cin >> key)) {
            cout << "некорректное значение\n";
            exit(EXIT_FAILURE);
        }
        key = toLower(key);
        break;
    case 4:
        cout << "Enter year: ";
        if (!(cin >> yr)) {
            cout << "некорректное значение\n";
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
            cout << "Found: " << cars[i].brand << " " << cars[i].model << " "
                << cars[i].year << " " << cars[i].color << " " << cars[i].number << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
}

void searchClient() {
    int choice;
    cout << "Search client by: 1.Surname 2.Price range\nChoice: ";
    if (!(cin >> choice)) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    bool found = false;
    if (choice == 1) {
        string surname;
        cout << "Enter surname: ";
        if (!(cin >> surname)) {
            cout << "некорректное значение\n";
            exit(EXIT_FAILURE);
        }
        surname = toLower(surname);
        for (int i = 0; i < clientCount; i++) {
            if (toLower(clients[i].surname) == surname) {
                cout << "Found: " << clients[i].name << " "
                    << clients[i].middle << " " << clients[i].surname << "\n";
                found = true;
                break;
            }
        }
    }
    else if (choice == 2) {
        double minP, maxP;
        cout << "Enter minimum and maximum price: ";
        if (!(cin >> minP >> maxP)) {
            cout << "некорректное значение\n";
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < clientCount; i++) {
            if (clients[i].price >= minP && clients[i].price <= maxP) {
                cout << "Found: " << clients[i].name << " "
                    << clients[i].middle << " " << clients[i].surname
                    << " Price: " << clients[i].price << "\n";
                found = true;
                break;
            }
        }
    }
    else {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    if (!found) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
}

void deleteEntry() {
    int choice;
    cout << "Delete: 1.Car 2.Client 3.All\nChoice: ";
    if (!(cin >> choice)) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    if (choice == 1) {
        string num;
        cout << "Enter the car number to delete: ";
        if (!(cin >> num)) {
            cout << "некорректное значение\n";
            exit(EXIT_FAILURE);
        }
        num = toLower(num);
        bool found = false;
        for (int i = 0; i < carCount; i++) {
            if (toLower(cars[i].number) == num) {
                for (int j = i; j < carCount - 1; j++)
                    cars[j] = cars[j + 1];
                carCount--;
                cout << "Car deleted.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "некорректное значение\n";
            exit(EXIT_FAILURE);
        }
    }
    else if (choice == 2) {
        string surname;
        cout << "Enter client's surname: ";
        cin.ignore();
        getline(cin, surname);
        surname = toLower(surname);
        bool found = false;
        for (int i = 0; i < clientCount; i++) {
            if (toLower(clients[i].surname) == surname) {
                for (int j = i; j < clientCount - 1; j++)
                    clients[j] = clients[j + 1];
                clientCount--;
                cout << "Client deleted.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "некорректное значение\n";
            exit(EXIT_FAILURE);
        }
    }
    else if (choice == 3) {
        carCount = clientCount = 0;
        cout << "All data deleted.\n";
    }
    else {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
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
    cout << "Enter client's surname: ";
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
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    string today;
    cout << "Enter today's date (dd/mm/yyyy): ";
    if (!(cin >> today)) {
        cout << "некорректное значение\n";
        exit(EXIT_FAILURE);
    }
    int diff = convertToDays(today) - convertToDays(clients[idx].rentDate);
    if (diff < 0)
        diff = 0;
    cout << "Debt for " << clients[idx].name << " " << clients[idx].surname
        << " is: " << diff * clients[idx].price << "\n";
}

#endif // FUNCTIONS_H
