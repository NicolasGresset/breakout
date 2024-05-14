#ifndef DIRECTION_H
#define DIRECTION_H

#include "utils/vector2D.h"

class Direction {
private:
  double x_;
  double y_;

  bool is_valid_ = true;

public:
  Direction();
  Direction(double x, double y);
  Direction(bool is_valid);

  inline bool isValid() const { return is_valid_; };
  inline void setValid(bool valid) { is_valid_ = valid; }

  inline Vector2D getVector() const { return Vector2D(x_, y_); }
};

#endif