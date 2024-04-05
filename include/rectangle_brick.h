#ifndef RECTANGLE_BRICK_H
#define RECTANGLE_BRICK_H

#include "brick.h"
#include "color.h"
#include "vector2D.h"

class RectangleBrick : public Brick {

public:
  RectangleBrick();
  RectangleBrick(Vector2D position, Color color, int life);
};

#endif