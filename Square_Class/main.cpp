#include "Square.h"
using namespace std;
#include <iostream>
int main() {

    Square square;

    square.setLength(5);
    square.setWidth(4);
    double area = square.calculateArea();
    cout << "The area is: " << area << endl;



    return 0;
}