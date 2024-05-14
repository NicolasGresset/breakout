#ifndef COLLISION_ENINE_H
#define COLLISION_ENINE_H

#include "object/line.h"
#include <memory>
#include <vector>

class Bonus;
class Game;
class Triangle;
class Ball;
class Rectangle;
class RectangleBrick;
class TriangleBrick;
class Brick;

using balls_ptr = std::shared_ptr<std::vector<std::shared_ptr<Ball>>>;

class CollisionEngine {

public:
  CollisionEngine();
  void resolveCollisions(Game &game);
  static Line isCollisionCircleRect(Ball &ball, Rectangle &rectangle);
  static Line isCollisionCircleTriangle(Ball &ball, Triangle &triangle);

private:
  Line isCollisionCircleBrick(Ball &ball, RectangleBrick &brick) const;
  Line isCollisionCircleBrick(Ball &ball, TriangleBrick &brick) const;

  bool isAABBCollision(Rectangle &rectangle1, Rectangle &rectangle2);

  bool isOutofWindow(Rectangle &rectangle, int width, int height);

  void manageCollisionBrickBall(std::shared_ptr<Brick> brick,
                                std::shared_ptr<Ball> ball, Game &game);
};

#endif