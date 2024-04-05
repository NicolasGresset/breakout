#include "../include/rectangle_brick.h"

RectangleBrick::RectangleBrick(Vector2D position, Color color, int life)
    : Brick(position, color, life) {};
RectangleBrick::RectangleBrick() : Brick(Vector2D{0, 0}, Color::blue, 3){};
