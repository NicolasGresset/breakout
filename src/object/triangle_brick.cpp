#include "object/triangle_brick.h"

TriangleBrick::TriangleBrick(Vector2D position, texture_ptr texture, int life,
                             double orientation, double length)
    : Object(position, texture), Triangle(orientation, length), Brick(life) {}
TriangleBrick::TriangleBrick() : Object(), Triangle(), Brick(){};