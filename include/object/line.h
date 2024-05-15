#ifndef LINE_H
#define LINE_H

#include "utils/vector2D.h"

/**
 * @brief A line is a geometrical object which corresponds to the vertex of an Object
 * 
 */
class Line {
private:
  Vector2D start_;
  Vector2D end_;

public:
  Line();
  Line(Vector2D start, Vector2D end);
  Line(bool is_valid);

  inline Vector2D getDirection() const {
    return Vector2D(end_.x_ - start_.x_, end_.y_ - start_.y_);
  }

  inline Vector2D getStart() const { return start_; };
  inline Vector2D getEnd() const { return end_; };
};

#endif