#include <iostream>
#include "data.h"
#include <cstdlib>
using namespace std;

#define COLOR_RESET      "\033[0m"
#define COLOR_RED        "\033[31m"
#define COLOR_GREEN      "\033[32m"
#define COLOR_DARK_GREEN "\033[2;32m"  
#define COLOR_CYAN       "\033[36m"
#define COLOR_BLUE       "\033[34m"
#define COLOR_GRAY       "\033[90m"
#define COLOR_YELLOW     "\033[33m"

void clearScreen() {
    system("cls||clear");
}

int main() {
    loadData();
    int choice;
    do {
        clearScreen();
        cout << COLOR_YELLOW
            << "&&&&   &&&&  &  &  &&&&&&    &&&&      &&&    &&&&   &&&&\n"
            << "&&  &  &     && &    &      &    &    &   &  &    &  &   &\n"
            << "&&&&&  &&&&  & &&    &      &&&&&&    &      &&&&&&  &&&&&&\n"
            << "&&  && &     &  &    &      &    &    &   &  &    &  &     &\n"
            << "&&  && &&&&  &  &    &      &    &     &&&&  &    &  &      &\n\n"
            << "\t\t           _____\n"
            << "\t\t       ___/__|__\\____\n"
            << "\t\t      |           |  |\n"
            << "\t\t      |___\\_____/_|__|\n"
            << "\t\t        (o)     (o)\n\n"
            << COLOR_RESET
            << COLOR_YELLOW "\t\t  Car Rental System Menu:\n\n" COLOR_RESET
            << COLOR_GREEN "1. Add car/client/contract\n" COLOR_RESET
            << COLOR_DARK_GREEN "2. Show cars/clients/contract\n" COLOR_RESET
            << COLOR_CYAN "3. Search (car/client/contract)\n" COLOR_RESET
            << COLOR_RED "4. Delete (entry/all data)\n" COLOR_RESET
            << COLOR_BLUE "5. Calculate debt\n" COLOR_RESET
            << COLOR_GRAY "6. Exit\n" COLOR_RESET
            << "Enter your choice: ";
        if (!(cin >> choice)) {
            cout << COLOR_RED "\nInvalid input. Exiting...\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        clearScreen();
        switch (choice) {
        case 1: {
            int sub;
            cout << COLOR_GREEN "Add: 1.Car 2.Client 3.Contract\nChoice: " COLOR_RESET;
            if (!(cin >> sub)) {
                cout << COLOR_RED "\nInvalid input. Exiting...\n" COLOR_RESET;
                exit(EXIT_FAILURE);
            }
            clearScreen();
            if (sub == 1)
                addCar();
            else if (sub == 2)
                addClient();
            else if (sub == 3)
                addContract();
            else {
                cout << COLOR_RED "Invalid choice. Exiting...\n" COLOR_RESET;
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 2: {
            int sub;
            cout << COLOR_DARK_GREEN "Show: 1.Cars 2.Clients 3.Contracts\nChoice: " COLOR_RESET;
            if (!(cin >> sub)) {
                cout << COLOR_RED "\nInvalid input. Exiting...\n" COLOR_RESET;
                exit(EXIT_FAILURE);
            }
            clearScreen();
            if (sub == 1)
                displayCars();
            else if (sub == 2)
                displayClients();
            else if (sub == 3)
                displayContracts();
            else {
                cout << COLOR_RED "Invalid choice. Exiting...\n" COLOR_RESET;
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 3: {
            int sub;
            cout << COLOR_CYAN "Search: 1.Car 2.Client 3.Contract\nChoice: " COLOR_RESET;
            if (!(cin >> sub)) {
                cout << COLOR_RED "\nInvalid input. Exiting...\n" COLOR_RESET;
                exit(EXIT_FAILURE);
            }
            clearScreen();
            if (sub == 1)
                searchCar();
            else if (sub == 2)
                searchClient();
            else if (sub == 3)
                searchContract();
            else {
                cout << COLOR_RED "Invalid choice. Exiting...\n" COLOR_RESET;
                exit(EXIT_FAILURE);
            }
            break;
        }
        case 4:
            deleteEntry();
            break;
        case 5:
            calcDebt();
            break;
        case 6:
            cout << COLOR_GRAY "Exiting and saving data...\n" COLOR_RESET;
            saveData();
            break;
        default:
            cout << COLOR_RED "Invalid choice. Exiting...\n" COLOR_RESET;
            exit(EXIT_FAILURE);
        }
        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 6);
    return 0;
}