#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"
#include "utils/constants.h"
#include "utils/vector2D.h"

class Line;

// each triangle is equilateral and is represented by its orientation
// the position of the triangle is, such as every object, the position of its
// center

/**
 * @brief A triangle IS equilateral and is unambiguously defined by its
 * position, length and orientation Inherits virtually from Object to solve
 * diamond's issue
 *
 */
class Triangle : virtual public Object {
protected:
  double orientation_;
  double length_; // the length of a side

public:
  Triangle();
  Triangle(double orientation, double length);
  Triangle(Vector2D position, texture_ptr texture, double orientation,
           double lenght);

  // returns the upper-left coordinates of the rounding rectangle of the
  // triangle
  inline Vector2D toUpperLeftCoords() const override {
    return Vector2D(position_.x_ - length_ / 2,
                    position_.y_ - SQUARE_ROOT_3 * length_ / 4);
  }

  void draw(SDL_Renderer &renderer) const override;

  std::vector<Vector2D> getVertices() const;

  std::vector<Line> getEdges() const;
};

#endif