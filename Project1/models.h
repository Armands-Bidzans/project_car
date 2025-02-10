#ifndef MODELS_H
#define MODELS_H
using namespace std;
#include <string>

struct Car {
    string brand;
    string model;
    string color;
    string number;
    int year;
};

struct Client {
    string name;
    string middle;
    string surname;
    string rentDate;
    double price;
};

#endif // MODELS_H