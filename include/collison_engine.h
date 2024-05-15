#ifndef COLLISION_ENINE_H
#define COLLISION_ENINE_H

#include "utils/direction.h"
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
class Line;

using balls_ptr = std::shared_ptr<std::vector<std::shared_ptr<Ball>>>;

class CollisionEngine {

public:
  CollisionEngine();
  void resolveCollisions(Game &game);

  // returns normal to impact if there is collision or invalid direction
  static Direction checkCollision(Ball &ball, Rectangle &rectangle);
  static Direction checkCollision(Ball &ball, Triangle &triangle);
  static Direction checkCollision(Ball &ball, RectangleBrick &brick);
  static Direction checkCollision(Ball &ball, TriangleBrick &brick);
  static Direction checkCollision(Ball &ball, Line &line);
  static Direction checkCollision(Ball &ball, Vector2D &point);
  static Direction checkCollision(Rectangle &rectangle1, Rectangle &rectangle2);

private:

  bool isOutofWindow(Rectangle &rectangle, int width, int height);

  void manageCollisionBrickBall(std::shared_ptr<Brick> brick,
                                std::shared_ptr<Ball> ball, Game &game);
};

#endif