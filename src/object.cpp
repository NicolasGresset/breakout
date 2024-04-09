#include "../include/object.h"
#include <cstddef>

Object::Object() : position_(0, 0), texture_(nullptr){};

Object::Object(Vector2D position, SDL_Texture *texture)
    : position_{position}, texture_(texture){};