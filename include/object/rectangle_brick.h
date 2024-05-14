#ifndef RECTANGLE_BRICK_H
#define RECTANGLE_BRICK_H

#include "brick.h"
#include "collison_engine.h"
#include "object/object.h"
#include "rectangle.h"
#include "utils/vector2D.h"
#include <SDL2/SDL_render.h>
#include "line.h"


class RectangleBrick : public Rectangle, public Brick {

public:
  RectangleBrick();
  RectangleBrick(Vector2D position, texture_ptr texture, int life,
                 double width, double height);

  inline void draw(SDL_Renderer &renderer) const override {
    if (!destroyed_) {
      Rectangle::draw(renderer);
    }
  }

  inline Vector2D toUpperLeftCoords() const override {
    return Rectangle::toUpperLeftCoords();
  }

   inline Direction isCollisionCircle(Ball &ball)  override {
    return CollisionEngine::checkCollision(ball, *this);
   }
};

#endif