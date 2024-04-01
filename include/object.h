#ifndef Object_H
#define Object_H

#include "color.h"
#include "position.h"

/*
An Object is a class which represents anything present in the screen that can
interact with other Objects, such as a brick and a ball for instance.

It must have a Position, a Color

This class is intended to be virtual and be specialized into Brick, Dock or Ball
*/
class Object {
  Position position_;
  Color color_;
};

#endif