#ifndef Object_H
#define Object_H

#include "color.h"
#include "vector2D.h"

/*
An Object is a class which represents anything present in the screen that can
interact with other Objects, such as a brick and a ball for instance.

It must have a Position, a Color

This class is intended to be virtual and be specialized into Brick, Dock or Ball
*/
class Object {
  protected:
  Vector2D position_;
  Color color_;

  public:
    Object();
    Object(Vector2D position, Color color);
};

#endif