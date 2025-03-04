#ifndef MODELS_H
#define MODELS_H
using namespace std;
#include <string>

struct Car {
    string brand;
    string model;
    string color;
    string number;
    double price;
    short year;
};

struct Client {
    string name;
    string middle;
    string surname;
    string rentDate;
};

struct Contract {
    string name; // Имя клиента
    string surname; // Фамилия клиента
    string middleName; // Отчество клиента
    string registrationNumber; // Регистрационный номер клиента
    string carBrand; // Марка автомобиля
    string carModel; // Модель автомобиля
    string carColor; // Цвет автомобиля
    string carNumber; // Номер автомобиля
    short carYear; // Год выпуска автомобиля
    short carPrice; // Цена аренды автомобиля
    string startDay; // Дата начала аренды
    string endDay; // Дата окончания аренды
    short rentDays; // Количество дней аренды
    short totalRentalPrice; // Общая стоимость аренды
};

#endif // MODELS_H