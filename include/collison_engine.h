#ifndef COLLISION_ENINE_H
#define COLLISION_ENINE_H

#include "ball.h"
#include "grid.h"
#include <vector>

/*
Collision detection is intrisically linked to the shape of bricks composing the
grid, thus a template class is required
*/

// template <typename T>  // on essaye de faire une classe normale pour
// l'instant
class CollisionEngine {
private:
  Ball *ball;
  Grid *grid;

public:
  CollisionEngine();
  CollisionEngine(Ball *ball, Grid *grid);
  ~CollisionEngine();

  /* Starting from a state of the positions of the game, move them in a way
   * there are*/
  void resolveCollisions();
};

#endif