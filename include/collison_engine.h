#ifndef COLLISION_ENINE_H
#define COLLISION_ENINE_H

#include "ball.h"
#include "grid.h"
#include <vector>

/*
Collision detection is intrisically linked to the shape of bricks composing the
grid, thus a template class is required
*/

template <typename T> class CollisionEngine {
private:
  Ball *ball;
  Grid<T> *grid;

public:
  CollisionEngine();
  ~CollisionEngine();

  void resolveCollisions();
};

#endif