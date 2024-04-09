#ifndef RECTANGLE_BRICK_H
#define RECTANGLE_BRICK_H

#include "brick.h"
#include "color.h"
#include "vector2D.h"
#include <SDL2/SDL_render.h>

class RectangleBrick : public Brick {
private:
  double width_;
  double height_;

public:
  RectangleBrick();
  RectangleBrick(Vector2D position = Vector2D{0, 0},
                 SDL_Texture *texture = nullptr, int life = 3, double width = 0,
                 double height = 0);

  /*
  Returns the 2DVector corresopnding to the coordinates of the upper left corner
  of the rectangle
  */
  Vector2D toUpperLeftCoords() const;

  void draw(SDL_Renderer *renderer) const override;
};

#endif