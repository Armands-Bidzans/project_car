#include <iostream>
#include "data.h"

using namespace std;

int main() {
    loadData();
    int choice;
    do {
        cout << "\nCar Rental System Menu:\n"
            << "1. Add car\n"
            << "2. Add client\n"
            << "3. Show cars\n"
            << "4. Show clients\n"
            << "5. Search (car/client)\n"
            << "6. Delete (entry/all data)\n"
            << "7. Calculate client debt\n"
            << "8. Exit\n"
            << "Enter your choice: ";
        cin >> choice;
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
            cout << "Search: 1.Car 2.Client\nChoice: ";
            cin >> sub;
            if (sub == 1)
                searchCar();
            else if (sub == 2)
                searchClient();
            else
                cout << "Invalid choice.\n";
            break;
        }
        case 6:
            deleteEntry();
            break;
        case 7:
            calcDebt();
            break;
        case 8:
            cout << "Exiting and saving data...\n";
            saveData();
            break;
        default:
            cout << "Invalid choice. Please enter 1-8.\n";
            exit(EXIT_FAILURE);
        }
    } while (choice != 8);
    return 0;
}