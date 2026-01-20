#include "Square.h"
#include "Square.cpp"
using namespace std;
#include <iostream>
int main() {

    Square square;

    square.setLength(5);
    square.setWidth(4);
    double area = square.calculateArea();
    std::cout << "The area is: " << area << std::endl;



    return 0;
}