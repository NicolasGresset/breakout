#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "object.h"
#include "utils/vector2D.h"
#include <SDL_render.h>

/* Héritage virtuel pour résoudre le problème du diamant */
class Rectangle : virtual public Object {

private:
  double width_;
  double height_;

public:
  Rectangle();
  Rectangle(Vector2D position = Vector2D{0, 0}, SDL_Texture *texture = nullptr,
            double width = 0, double height = 0);
  /*
Returns the 2DVector corresopnding to the coordinates of the upper left corner
of the rectangle
*/
  inline Vector2D toUpperLeftCoords() const override {
    return Vector2D(position_.x_ - width_ / 2, position_.y_ - height_ / 2);
  }

  inline double getWidth() const { return width_; };
  inline double getHeight() const { return height_; }

  void draw(SDL_Renderer *renderer) const override;
};

#endif