#include <iostream>
#include "Cube.h"
#include "Cube.cpp"
using namespace std;
int main() {
    Cube cube;

    cube.setLength(22);
    double volume = cube.calculateVolume();
    cout << "The volume is: " << volume << endl;
    return 0;
}