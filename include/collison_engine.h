#ifndef COLLISION_ENINE_H
#define COLLISION_ENINE_H

#include "utils/direction.h"
#include <memory>

class Bonus;
class Game;
class Triangle;
class Ball;
class Rectangle;
class RectangleBrick;
class TriangleBrick;
class Brick;
class Line;
class LevelState;

class CollisionEngine {

public:
  CollisionEngine();
  static void resolveCollisions(LevelState &game);

  // returns normal to impact if there is collision or invalid direction
  static Direction checkCollision(Ball &ball, Rectangle &rectangle);
  static Direction checkCollision(Ball &ball, Triangle &triangle);
  static Direction checkCollision(Ball &ball, RectangleBrick &brick);
  static Direction checkCollision(Ball &ball, TriangleBrick &brick);
  static Direction checkCollision(Ball &ball, Line &line);
  static Direction checkCollision(Ball &ball, Vector2D &point);
  static Direction checkCollision(Rectangle &rectangle1, Rectangle &rectangle2);

private:
  static bool isOutofWindow(Rectangle &rectangle, int width, int height);

  static void manageCollisionBrickBall(std::shared_ptr<Brick> brick,
                                       std::shared_ptr<Ball> ball,
                                       LevelState &game);
};

#endif