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

string colors[MAX_COLORS];
int colorCount = 0;

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
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    if (colorCount == 0) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    Car c;
    cout << COLOR_GREEN << "Enter the car's brand, model, and year: " COLOR_RESET;
    if (!(cin >> c.brand >> c.model >> c.year)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }

    cout << COLOR_GREEN << "Available colors:\n" COLOR_RESET;
    for (int i = 0; i < colorCount; i++)
        cout << COLOR_GREEN << i + 1 << ". " << colors[i] << "  " COLOR_RESET;
    cout << COLOR_GREEN << "\nSelect a color (1-" << colorCount << "): " COLOR_RESET;

    int choice;
    if (!(cin >> choice)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    if (choice < 1 || choice > colorCount) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    c.color = colors[choice - 1];

    cout << COLOR_GREEN << "Enter the car's number: " COLOR_RESET;
    if (!(cin >> c.number)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    cars[carCount++] = c;
    cout << COLOR_GREEN << "Car added.\n" COLOR_RESET;
}

void addClient() {
    if (clientCount >= MAX_CLIENTS) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    Client cl;
    cout << COLOR_GREEN << "Enter the name, middle name, surname, rent date (dd/mm/yyyy), and price per day: " COLOR_RESET;
    if (!(cin >> cl.name >> cl.middle >> cl.surname >> cl.rentDate >> cl.price)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    clients[clientCount++] = cl;
    cout << COLOR_GREEN << "Client added.\n" COLOR_RESET;
}

void displayCars() {
    if (carCount == 0) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < carCount; i++)
        cout << COLOR_DARK_GREEN << cars[i].brand << " " << cars[i].model << " " << cars[i].year << " "
        << cars[i].color << " " << cars[i].number << "\n" COLOR_RESET;
}

void displayClients() {
    if (clientCount == 0) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < clientCount; i++)
        cout << COLOR_DARK_GREEN << clients[i].name << " " << clients[i].middle << " " << clients[i].surname << " "
        << clients[i].rentDate << " " << clients[i].price << "\n" COLOR_RESET;
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
            cout << COLOR_CYAN << "Found: " << cars[i].brand << " " << cars[i].model << " "
                << cars[i].year << " " << cars[i].color << " " << cars[i].number << "\n" COLOR_RESET;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
}

void searchClient() {
    int choice;
    cout << COLOR_CYAN << "Search client by: 1.Surname 2.Price range\nChoice: " COLOR_RESET;
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
                cout << COLOR_CYAN << "Found: " << clients[i].name << " "
                    << clients[i].middle << " " << clients[i].surname << "\n" COLOR_RESET;
                found = true;
                break;
            }
        }
    }
    else if (choice == 2) {
        double minP, maxP;
        cout << COLOR_CYAN << "Enter minimum and maximum price: " COLOR_RESET;
        if (!(cin >> minP >> maxP)) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < clientCount; i++) {
            if (clients[i].price >= minP && clients[i].price <= maxP) {
                cout << COLOR_CYAN << "Found: " << clients[i].name << " "
                    << clients[i].middle << " " << clients[i].surname
                    << " Price: " << clients[i].price << "\n" COLOR_RESET;
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
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
}

void deleteEntry() {
    int choice;
    cout << COLOR_RED << "Delete: 1.Car 2.Client 3.All\nChoice: " COLOR_RESET;
    if (!(cin >> choice)) {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
        exit(EXIT_FAILURE);
    }
    if (choice == 1) {
        string num;
        cout << COLOR_RED << "Enter the car number to delete: " COLOR_RESET;
        if (!(cin >> num)) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        num = toLower(num);
        bool found = false;
        for (int i = 0; i < carCount; i++) {
            if (toLower(cars[i].number) == num) {
                for (int j = i; j < carCount - 1; j++)
                    cars[j] = cars[j + 1];
                carCount--;
                cout << COLOR_RED << "Car deleted.\n" COLOR_RESET;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
    }
    else if (choice == 2) {
        string surname;
        cout << COLOR_RED << "Enter client's surname: " COLOR_RESET;
        cin.ignore();
        getline(cin, surname);
        surname = toLower(surname);
        bool found = false;
        for (int i = 0; i < clientCount; i++) {
            if (toLower(clients[i].surname) == surname) {
                for (int j = i; j < clientCount - 1; j++)
                    clients[j] = clients[j + 1];
                clientCount--;
                cout << COLOR_RED << "Client deleted.\n" COLOR_RESET;
                found = true;
                break;
            }
        }
        if (!found) {
            cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
    }
    else if (choice == 3) {
        carCount = clientCount = 0;
        cout << COLOR_RED << "All data deleted.\n" COLOR_RESET;
    }
    else {
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
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
        cout << COLOR_RED << "incorrect value\n" COLOR_RESET;
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
    cout << COLOR_BLUE << "Debt for " << clients[idx].name << " " << clients[idx].surname
        << " is: " << diff * clients[idx].price << "\n" COLOR_RESET;
}

#endif // FUNCTIONS_H