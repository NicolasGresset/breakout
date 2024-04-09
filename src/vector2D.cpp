#include "../include/vector2D.h"
#include <iostream>

Vector2D::Vector2D(double x, double y) : x_(x), y_(y){};

void Vector2D::print() const {
  std::cout << "(" << x_ << "," << y_ << ")" << std::endl;
}