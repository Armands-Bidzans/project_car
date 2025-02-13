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
    int year;
};

struct Client {
    string name;
    string middle;
    string surname;
    string rentDate;
};

#endif // MODELS_H