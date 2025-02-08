#ifndef DATA_H
#define DATA_H

#include "models.h"
#include <string>

const int MAX_CARS = 100;
const int MAX_CLIENTS = 100;
const int MAX_COLORS = 20;

extern Car cars[MAX_CARS];
extern Client clients[MAX_CLIENTS];
extern int carCount;
extern int clientCount;

extern std::string colors[MAX_COLORS];
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
int convertToDays(const std::string& date);
void calcDebt();

#endif // DATA_H