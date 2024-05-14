#include "object/line.h"

Line::Line() {}

Line::Line(Vector2D start, Vector2D end) : start_(start), end_(end) {}

Line::Line(bool is_valid) : is_valid_(is_valid) {}