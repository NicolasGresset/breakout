#ifndef COLLISION_ENINE_H
#define COLLISION_ENINE_H

#include "ball.h"
#include "grid.h"
#include <vector>

class CollisionEngine {
private:
  Ball *ball;
  Grid *grid;

public:
    CollisionEngine();
    ~CollisionEngine();
    
    void resolveCollisions();
};

#endif