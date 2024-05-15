#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
class Vector2D {
public:
  double x_;
  double y_;

public:
  Vector2D(double x = 0, double y = 0);
  Vector2D(const Vector2D &vector);

  inline double dotProduct(Vector2D &other) const {
    return x_ * other.x_ + y_ * other.y_;
  }

  void print(void) const;

  // the vectorial product between 2 coplanars vectors can be fully identified
  // to a scalar, hence the prototype
  inline double vectorialProduct(Vector2D &other) const {
    return x_ * other.y_ - y_ * other.x_;
  }

  inline double getNorm() const { return sqrt(pow(x_, 2) + pow(y_, 2)); }

  inline double getSquaredNorm() const { return pow(x_, 2) + pow(y_, 2); }

  Vector2D rotate(double theta) const {
    return Vector2D(cos(theta) * x_ - sin(theta) * y_,
                    sin(theta * x_) + cos(theta) * y_);
  }

  Vector2D rotate(double theta, Vector2D center) const {
    Vector2D new_coords = Vector2D(x_- center.x_, y_ - center.y_).rotate(theta);
    new_coords.x_ += center.x_;
    new_coords.y_ += center.y_;
    return new_coords;
  }

  inline double getAngle() const {
    return tan(y_/x_);
  }
};

#endif
