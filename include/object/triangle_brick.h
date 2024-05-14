#ifndef TRIANGLE_BRICK_H
#define TRIANGLE_BRICK_H

#include "object/brick.h"
#include "object/triangle.h"

class TriangleBrick : public Triangle, public Brick {
public:
  TriangleBrick();
  TriangleBrick(Vector2D position, texture_ptr texture, int life, double width,
                double height);
};

#endif