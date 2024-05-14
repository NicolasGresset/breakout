#ifndef BRICK_H
#define BRICK_H

#include "gui/color.h"
#include "object.h"
#include "utils/vector2D.h"
#include <SDL2/SDL_render.h>

class Ball;
class Line;

class Brick : virtual public Object {
private:
  int life_;

protected:
  bool destroyed_ = false;

public:
  Brick();
  Brick(Vector2D position, texture_ptr texture, int life);
  Brick(int life);

  void decrementLife(int number);
  inline bool isDestroyed() const { return destroyed_; }

  // returns normal to collision if there is or special value instead
  virtual Line isCollisionCircle(Ball &ball)  = 0;
};

#endif