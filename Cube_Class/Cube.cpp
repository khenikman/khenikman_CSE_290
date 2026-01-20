#include "Cube.h"

void Cube::setLength(double length) {
    length_ = length;
}



double Cube::calculateVolume() {
   return length_ * length_ * length_;
}