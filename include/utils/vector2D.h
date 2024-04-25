#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
public:
  double x_;
  double y_;

public:
  Vector2D(double x = 0, double y = 0);
  Vector2D(const Vector2D &vector);


  void print(void) const;
};

#endif