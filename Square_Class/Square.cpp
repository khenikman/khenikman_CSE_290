#include "Square.h"

void Square::setLength(double length) {
    length_ = length;
}

void Square::setWidth(double width) {
    height_ = width;
}

double Square::calculateArea() {
   return length_ * height_;
}