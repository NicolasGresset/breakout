#include "../include/brick.h"
#include <SDL2/SDL_render.h>

Brick::Brick() : Object(), life_{3} {};

Brick::Brick(Vector2D position, SDL_Texture *texture, int life)
    : Object(position, texture), life_(life){};