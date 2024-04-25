#include "utils/vector2D.h"
#include <iostream>

Vector2D::Vector2D(double x, double y) : x_(x), y_(y){};
Vector2D::Vector2D(const Vector2D &vector) : x_(vector.x_), y_(vector.y_){};

void Vector2D::print() const {
  std::cout << "(" << x_ << "," << y_ << ")" << std::endl;
}