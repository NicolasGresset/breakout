#ifndef TRIANGLE_BRICK_H
#define TRIANGLE_BRICK_H

#include "collison_engine.h"
#include "line.h"
#include "object/brick.h"
#include "object/triangle.h"

class TriangleBrick : public Triangle, public Brick {
public:
  TriangleBrick();
  TriangleBrick(Vector2D position, texture_ptr texture, int life,
                double orientation, double length);

  inline Vector2D toUpperLeftCoords() const override {
    return Triangle::toUpperLeftCoords();
  }

  inline void draw(SDL_Renderer &renderer) const override {
    if (!destroyed_) {
      Triangle::draw(renderer);
    }
  }

  Line isCollisionCircle(Ball &ball) override {
    return CollisionEngine::isCollisionCircleTriangle(ball, *this);
  };
};

#endif