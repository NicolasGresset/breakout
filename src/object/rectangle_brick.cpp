#include "object/rectangle_brick.h"

RectangleBrick::RectangleBrick(Vector2D position, texture_ptr texture,
                               int life, double width, double height)
    : Object(position, texture), Rectangle(width, height), Brick(life) {}
RectangleBrick::RectangleBrick() : Object(), Rectangle(), Brick(){};
