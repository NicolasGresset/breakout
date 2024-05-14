#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
public:
  double x_;
  double y_;

public:
  Vector2D(double x = 0, double y = 0);
  Vector2D(const Vector2D &vector);

  inline double dotProduct(Vector2D &other) {
    return x_ * other.x_ + y_ * other.y_;
  }

  void print(void) const;
};

#endif