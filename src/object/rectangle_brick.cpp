#include "object/rectangle_brick.h"
#include "object/brick.h"
#include "object/rectangle.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>

RectangleBrick::RectangleBrick(Vector2D position, std::shared_ptr<SDL_Texture> texture,
                               int life, double width, double height)
    : Rectangle(position, texture, width, height), Brick(life) {}
RectangleBrick::RectangleBrick() : Rectangle(), Brick(){};
