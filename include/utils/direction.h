#ifndef DIRECTION_H
#define DIRECTION_H

#include "utils/vector2D.h"

// A direction is a unit vector which represents the result of a Collision test:
// either the normal to the surface of impact if there is one or it is set as
// invalid if there is no collision
class Direction : public Vector2D {
private:
  bool is_valid_ = true;

public:
  Direction();
  Direction(double x, double y);
  Direction(bool is_valid);

  inline bool isValid() const { return is_valid_; };
  inline void setValid(bool valid) { is_valid_ = valid; }

  Vector2D getVector() const;
};

#endif