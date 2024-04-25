#ifndef BRICK_H
#define BRICK_H

#include "color.h"
#include "object.h"
#include "vector2D.h"
#include <SDL2/SDL_render.h>

class Brick : public Object {
private:
  int life_;

protected:
  bool destroyed_ = false;

public:
  Brick();
  Brick(Vector2D position, SDL_Texture *texture, int life);
  Brick(int life);

  void decrementLife(int number);
  inline const Vector2D &getPosition(void) const { return position_; }
};

#endif