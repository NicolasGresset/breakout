#include "../include/rectangle_brick.h"
#include "brick.h"
#include "rectangle.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>

RectangleBrick::RectangleBrick(Vector2D position, SDL_Texture *texture,
                               int life, double width, double height)
    : Rectangle(position, texture, width, height), Brick(life){};
RectangleBrick::RectangleBrick() : Rectangle(Vector2D{0, 0}, nullptr, 0, 0), Brick(3){};



