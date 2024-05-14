#include "object/line.h"

Line::Line() {}

Line::Line(double x, double y) : x_(x), y_(y) {}

Line::Line(bool is_valid) : is_valid_(is_valid) {}