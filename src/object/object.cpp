#include "object/object.h"
#include <cstddef>

Object::Object() : position_(0, 0), texture_(nullptr){};

Object::Object(Vector2D position, std::shared_ptr<SDL_Texture> texture)
    : position_{position}, texture_(texture){};

MovableObject::MovableObject(Vector2D position, std::shared_ptr<SDL_Texture> texture,
                             Vector2D speed)
    : Object(position, texture), speed_(speed){};

MovableObject::MovableObject(Vector2D speed) : Object(), speed_(speed) {}

MovableObject::MovableObject() : Object(), speed_() {}