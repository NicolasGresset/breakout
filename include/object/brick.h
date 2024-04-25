#ifndef BRICK_H
#define BRICK_H

#include "gui/color.h"
#include "object.h"
#include "utils/vector2D.h"
#include <SDL2/SDL_render.h>

class Brick : virtual public Object {
private:
  int life_;

protected:
  bool destroyed_ = false;

public:
  Brick();
  Brick(Vector2D position, SDL_Texture *texture, int life);
  Brick(int life);

  void decrementLife(int number);
};

#endif