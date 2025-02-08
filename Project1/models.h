#ifndef MODELS_H
#define MODELS_H

#include <string>

struct Car {
    std::string brand;
    std::string model;
    std::string color;
    std::string number;
    int year;
};

struct Client {
    std::string name;
    std::string middle;
    std::string surname;
    std::string rentDate;
    double price;
};

#endif // MODELS_H