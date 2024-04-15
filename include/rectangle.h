#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "object.h"
#include "vector2D.h"
#include <SDL_render.h>
class Rectangle : public Object {

private:
  double width_;
  double height_;

public:

    Rectangle();
    Rectangle(Vector2D position = Vector2D{0, 0}, SDL_Texture *texture = nullptr, double width = 0, double height = 0);
  /*
Returns the 2DVector corresopnding to the coordinates of the upper left corner
of the rectangle
*/
  inline Vector2D toUpperLeftCoords() const {
    return Vector2D(position_.getX() - width_ / 2,
                    position_.getY() - height_ / 2);
  }

  void draw(SDL_Renderer *renderer) const override;
};

#endif