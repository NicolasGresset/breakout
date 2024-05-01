#include "object/rectangle_brick.h"
#include "object/brick.h"
#include "object/object.h"
#include "object/rectangle.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>

RectangleBrick::RectangleBrick(Vector2D position, texture_ptr texture,
                               int life, double width, double height)
    : Object(position, texture), Rectangle(width, height), Brick(life) {}
RectangleBrick::RectangleBrick() : Object(), Rectangle(), Brick(){};
