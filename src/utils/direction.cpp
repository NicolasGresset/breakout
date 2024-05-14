#include "utils/direction.h"
#include "utils/vector2D.h"

Direction::Direction() {}

Direction::Direction(double x, double y) : x_(x), y_(y) {}

Direction::Direction(bool is_valid) : is_valid_(is_valid) {}

Vector2D Direction::getVector() const {
  double norm = sqrt(pow(x_, 2) + pow(y_, 2));
  return Vector2D(x_ / norm, y_ / norm);
}