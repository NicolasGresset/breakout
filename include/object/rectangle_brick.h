#ifndef RECTANGLE_BRICK_H
#define RECTANGLE_BRICK_H

#include "brick.h"
#include "rectangle.h"
#include "utils/vector2D.h"
#include <SDL2/SDL_render.h>

class RectangleBrick : public Rectangle, public Brick {

public:
  RectangleBrick();
  RectangleBrick(Vector2D position, std::shared_ptr<SDL_Texture> texture, int life,
                 double width, double height);

  inline void draw(SDL_Renderer &renderer) const override {
    if (!destroyed_) {
      Rectangle::draw(renderer);
    }
  }

  inline Vector2D toUpperLeftCoords() const override {
    return Rectangle::toUpperLeftCoords();
  }
};

#endif