#ifndef LINE_H
#define LINE_H

#include "utils/vector2D.h"

class Line {
private:
  Vector2D start_;
  Vector2D end_;

  bool is_valid_ = true;

public:
  Line();
  Line(Vector2D start, Vector2D end);
  Line(bool is_valid);

  inline bool isValid() const { return is_valid_; };
  inline void setValid(bool valid) { is_valid_ = valid; }

  inline Vector2D getDirection() const {
    return Vector2D(end_.x_ - start_.x_, end_.y_ - start_.y_);
  }
};

#endif