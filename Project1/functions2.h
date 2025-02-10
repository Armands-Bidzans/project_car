#pragma once
#ifndef FUNCTIONS2_H
#define FUNCTIONS2_H
using namespace std;
#include <string>
#include <algorithm>

inline string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

inline string toUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

#endif // FUNCTIONS2_H