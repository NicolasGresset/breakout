#ifndef RECTANGLE_BRICK_H
#define RECTANGLE_BRICK_H

#include "brick.h"
#include "rectangle.h"
#include "utils/vector2D.h"
#include <SDL2/SDL_render.h>

class RectangleBrick : public Rectangle, public Brick {

public:
  RectangleBrick();
  RectangleBrick(Vector2D position = Vector2D{0, 0},
                 SDL_Texture *texture = nullptr, int life = 3, double width = 0,
                 double height = 0);

  inline void draw(SDL_Renderer *renderer) const override {
    if (!destroyed_) {
      Rectangle::draw(renderer);
    }
  }

  inline Vector2D toUpperLeftCoords() const override {
    return Rectangle::toUpperLeftCoords();
  }
};

#endif