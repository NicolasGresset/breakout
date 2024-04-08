#include "../include/rectangle_brick.h"

RectangleBrick::RectangleBrick(Vector2D position = Vector2D{0, 0}, Color color = Color::blue, int life = 3, double width= 0, double height = 0)
    : Brick(position, color, life), width_(width), height_(height) {};
RectangleBrick::RectangleBrick() : Brick(Vector2D{0, 0}, Color::blue, 3){};

Vector2D RectangleBrick::toUpperLeftCoords() const{
    return 
}