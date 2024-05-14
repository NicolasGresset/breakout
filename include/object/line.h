#ifndef LINE_H
#define LINE_H

#include "utils/vector2D.h"

class Line {
private:
  double x_;
  double y_;

  bool is_valid_ = true;

public:
  Line();
  Line(double x, double y);
  Line(bool is_valid);

  inline bool isValid() const { return is_valid_; };
  inline void setValid(bool valid) { is_valid_ = valid; }

  inline Vector2D getDirection() const {
    return Vector2D(x_, y_);
  }
};

#endif