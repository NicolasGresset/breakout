#include "object/brick.h"

Brick::Brick() : Object(), life_{0} {};

Brick::Brick(Vector2D position, texture_ptr texture, int life)
    : Object(position, texture), life_(life){};

Brick::Brick(int life) : Object(), life_(life) {};


void Brick::decrementLife(int number) {
  life_ -= number;
  if (life_ <= 0) {
    destroyed_ = true;
  }
}
