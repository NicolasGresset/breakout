#include "../include/object.h"

Object::Object() : position_(0, 0), color_(Color::blue){};

Object::Object(Vector2D position, Color color)
    : position_{position}, color_{color} {};