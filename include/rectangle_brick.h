#ifndef RECTANGLE_BRICK_H
#define RECTANGLE_BRICK_H

#include "brick.h"
#include "color.h"
#include "vector2D.h"

class RectangleBrick : public Brick {
private:
double width_;
double height_;
public:
  RectangleBrick();
  RectangleBrick(Vector2D position, Color color, int life, double width, double height);

  /*
  Returns the 2DVector corresopnding to the coordinates of the upper left corner of the rectangle
  */
  Vector2D toUpperLeftCoords() const;
};

#endif