#include "DataObject.h"
#include <iostream> // header in standard library

using namespace Asset;
using namespace std;

class DataObject {
private:
    int number;
    float gpa;

public:
    DataObject(int number, float gpa) {
        this->number = number;
    }
    void print() {
        cout << "number : " << number << " gpa : " << gpa;
    }
    int getNumber() {
        return this->number;
    }
    int getGpa() {
        return this->number;
    }
};

