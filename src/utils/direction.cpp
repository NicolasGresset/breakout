#include "utils/direction.h"

Direction::Direction() {}

Direction::Direction(double x, double y) : x_(x), y_(y) {}

Direction::Direction(bool is_valid) : is_valid_(is_valid) {}