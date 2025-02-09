#include <iostream>
#include "data.h"
#include <cstdlib>

using namespace std;

#define COLOR_RESET      "\033[0m"
#define COLOR_RED        "\033[31m"
#define COLOR_GREEN      "\033[32m"
#define COLOR_DARK_GREEN "\033[2;32m"  // Темно-зеленый
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
        cout << COLOR_YELLOW "\nCar Rental System Menu:\n" COLOR_RESET
            << COLOR_GREEN "1. Add car\n"
            << "2. Add client\n" COLOR_RESET
            << COLOR_DARK_GREEN "3. Show cars\n"  // Темно-зеленый
            << "4. Show clients\n" COLOR_RESET    // Темно-зеленый
            << COLOR_CYAN "5. Search (car/client)\n" COLOR_RESET
            << COLOR_RED "6. Delete (entry/all data)\n" COLOR_RESET
            << COLOR_BLUE "7. Calculate client debt\n" COLOR_RESET
            << COLOR_GRAY "8. Exit\n" COLOR_RESET
            << "Enter your choice: ";
        cin >> choice;
        clearScreen();

        switch (choice) {
        case 1:
            addCar();
            break;
        case 2:
            addClient();
            break;
        case 3:
            displayCars();
            break;
        case 4:
            displayClients();
            break;
        case 5: {
            int sub;
            cout << COLOR_CYAN "Search: 1.Car 2.Client\nChoice: " COLOR_RESET;
            cin >> sub;
            clearScreen();
            if (sub == 1)
                searchCar();
            else if (sub == 2)
                searchClient();
            else {
                cout << COLOR_RED "Invalid choice.\n" COLOR_RESET;
            }
            break;
        }
        case 6:
            deleteEntry();
            break;
        case 7:
            calcDebt();
            break;
        case 8:
            cout << COLOR_GRAY "Exiting and saving data...\n" COLOR_RESET;
            saveData();
            break;
        default:
            cout << COLOR_RED "Invalid choice. Please enter 1-8.\n" COLOR_RESET;
            break;
        }
        if (choice != 8) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }
    } while (choice != 8);
    return 0;
}