#include "../include/brick.h"

Brick::Brick() : Object(), life_{3} {};

Brick::Brick(Vector2D position, Color color, int life)
    : Object(position, color), life_(life){};