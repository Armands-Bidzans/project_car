#ifndef DATA_H
#define DATA_H

#include "models.h"
#include <string>
using namespace std;
const int MAX_CARS = 100;
const int MAX_CLIENTS = 100;
const int MAX_COLORS = 20;

// Цветовые макросы
#define COLOR_RESET      "\033[0m"
#define COLOR_RED        "\033[31m"
#define COLOR_GREEN      "\033[32m"
#define COLOR_DARK_GREEN "\033[2;32m"  
#define COLOR_CYAN       "\033[36m"
#define COLOR_BLUE       "\033[34m"
#define COLOR_YELLOW     "\033[33m"

extern Car cars[MAX_CARS];
extern Client clients[MAX_CLIENTS];
extern int carCount;
extern int clientCount;

extern string colors[MAX_COLORS];
extern int colorCount;

void saveData();
void loadData();
void addCar();
void addClient();
void displayCars();
void displayClients();
void searchCar();
void searchClient();
void deleteEntry();
int convertToDays(const string& date);
void calcDebt();

#endif // DATA_H