#ifndef GAME_H
#define GAME_H

#include "SDL2Window.h"
#include "collison_engine.h"
#include "dock.h"
#include "grid.h"
/*
A game is composed of a SDL2Window which renders all the objects inside of it,
namely :
- Bricks to be destroyed by the player
- The (potentially many) ball
- The dock controlled by the player
- Bonuses

Each of these objects are Object which may collide with others.
More precisely, the ball can collide with both bricks and the dock, and bonuses
dropping down when bricks get destroyed can collide with the dock.

Hence, a CollisionEngine is required to handle such behaviour.

*/
class Game {
private:
  SDL2Window window_;
  CollisionEngine collision_engine_;
  Dock player_;
  Grid grid;
};

#endif