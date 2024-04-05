#ifndef BRICK_H
#define BRICK_H

#include "color.h"
#include "object.h"
#include "vector2D.h"

class Brick : public Object {
private:
  int life_;

public:
  Brick();
  Brick(Vector2D position, Color color, int life);
};

#endif