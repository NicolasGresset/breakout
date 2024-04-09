#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D {
private:
  double x_;
  double y_;

public:
  Vector2D(double x = 0, double y = 0);
  inline double getX(void) const { return x_; }
  inline double getY(void) const { return y_; }
};

#endif