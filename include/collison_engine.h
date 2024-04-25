#ifndef COLLISION_ENINE_H
#define COLLISION_ENINE_H

#include "ball.h"
#include "dock.h"
#include "grid.h"
#include "rectangle.h"
#include "rectangle_brick.h"
#include "vector2D.h"
#include <vector>
/*
Collision detection is intrisically linked to the shape of bricks composing the
grid, thus a template class is required
*/

// template <typename T>  // on essaye de faire une classe normale pour
// l'instant
class CollisionEngine {
private:
  std::vector<Ball> &balls_;
  Grid &grid_;
  Dock &player_;

public:
  CollisionEngine();
  CollisionEngine(std::vector<Ball> &balls, Grid &grid, Dock &player);
  //~CollisionEngine();

  /* Starting from a state of the positions of the game, move them in a way
   * there are*/
  void resolveCollisions();


private:

  bool isCollisionCircleRect(Ball & ball, Rectangle& rectangle) const;
  bool checkAABBCollision();
  // returns 0 if there are no intersections or the point of collision otherwise
  // bool ballIntersectRectangle(Ball &ball, RectangleBrick &brick) const;
};

#endif