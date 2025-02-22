#ifndef DATA_H
#define DATA_H
#include <string>
using namespace std;
const int MAX_CARS = 100;
const int MAX_CLIENTS = 100;
const int MAX_CONTRACTS = 100;

#define COLOR_RESET      "\033[0m"
#define COLOR_RED        "\033[31m"
#define COLOR_GREEN      "\033[32m"
#define COLOR_DARK_GREEN "\033[2;32m"  
#define COLOR_CYAN       "\033[36m"
#define COLOR_BLUE       "\033[34m"
#define COLOR_YELLOW     "\033[33m"

struct Car {
    string brand;
    string model;
    string color;
    string number;
    int price;
    int year;
};

struct Client {
    string name;
    string middle;
    string surname;
};

struct Contract {
    string name;
    string surname;
    string middleName;
    string registrationNumber;
    string carBrand;
    string carModel;
    string startDay;
    string endDay;
    short rentDays;
    short totalRentalPrice;
};

extern Car cars[MAX_CARS];
extern Client clients[MAX_CLIENTS];
extern Contract contracts[MAX_CONTRACTS];
extern int carCount;
extern int clientCount;
extern int contractCount;

void saveData();
void loadData();
void addCar();
void addClient();
void addContract();
void displayCars();
void displayClients();
void displayContracts();
void searchCar();
void searchClient();
void searchContract();
void deleteEntry();
int convertToDays(const string& date);
void calcDebt();

enum colormenu {
    Red,
    Blue,
    Black,
    White,
    Silver,
    Gray,
    Green,
    Yellow,
    Orange,
    Purple,
    Pink,
    Brown,
    Gold,
    Beige,
    Light_Blue,
    Lime,
    Magenta,
    Turquoise,
    Khaki,
    Burgundy,
    Indigo,
    Azure,
    Crimson,
    Olive,
    Peach,
    Terracotta,
    Fuchsia,
    Chocolate,
    Amber,
    Aquamarine,
    Graphite,
    Emerald,
    Chestnut,
    Coral,
    Lemon,
    Copper,
    Jade,
    Ruby,
    Sapphire,
    Gray_Brown_Crimson,
    Steel,
    Pistachio,
    Ink,
    Saffron
};

const string colorStrings[] = {
    "Red", "Blue", "Black", "White", "Silver", "Gray", "Green", "Yellow",
    "Orange", "Purple", "Pink", "Brown", "Gold", "Beige", "Light Blue", "Lime",
    "Magenta", "Turquoise", "Khaki", "Burgundy", "Indigo", "Azure", "Crimson",
    "Olive", "Peach", "Terracotta", "Fuchsia", "Chocolate", "Amber", "Aquamarine",
    "Graphite", "Emerald", "Chestnut", "Coral", "Lemon", "Copper", "Jade", "Ruby",
    "Sapphire", "Gray-Brown-Crimson", "Steel", "Pistachio", "Ink", "Saffron"
};

#endif // DATA_H