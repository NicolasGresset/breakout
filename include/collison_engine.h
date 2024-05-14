#ifndef COLLISION_ENINE_H
#define COLLISION_ENINE_H

#include "grid.h"
#include "object/ball.h"
#include "object/dock.h"
#include "object/rectangle.h"
#include "object/rectangle_brick.h"
#include "utils/vector2D.h"
#include <memory>
#include <vector>
/*
Collision detection is intrisically linked to the shape of bricks composing the
grid, thus a template class is required
*/

// template <typename T>  // on essaye de faire une classe normale pour
// l'instant

class Bonus;
class Game;

using balls_ptr = std::shared_ptr<std::vector<std::shared_ptr<Ball>>>;

class CollisionEngine {

public:
  CollisionEngine();
  void resolveCollisions(Game &game);

private:
  bool isCollisionCircleRect(Ball &ball, Rectangle &rectangle) const;
  bool isAABBCollision(Rectangle &rectangle1, Rectangle &rectangle2);

  bool isOutofWindow(Rectangle &rectangle, int width, int height);

  bool manageCollisionBrickBall(std::shared_ptr<Brick> brick,
                                std::shared_ptr<Ball> ball);
};

#endif