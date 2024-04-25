#ifndef GAME_H
#define GAME_H

#include "SDL2Window.h"
#include "assets.h"
#include "ball.h"
#include "collison_engine.h"
#include "dock.h"
#include "grid.h"
#include <SDL_render.h>

/*
A game is composed of a SDL2Window which renders all the objects inside of it,
namely :
- Bricks to be destroyed by the player
- The (potentially many) ball(s)
- The dock controlled by the player
- Bonuses

Each of these objects are Object which may collide with others.
More precisely, the ball can collide with both bricks and the dock, and bonuses
dropping down when bricks get destroyed can collide with the dock.

Hence, a CollisionEngine is required to handle such behaviour.

A game is parametrized by the type of bricks it is composed : either rectangles
or hexagons

*/

// template<typename T>
class Game {
private:
  SDL2Window window_;
  SDL_Renderer *renderer_; // shared_pointer to renderer to avoir getting it too
                           // often from Window member
  CollisionEngine collision_engine_;
  Dock player_;
  Grid grid_;
  std::vector<Ball> balls_;
  Assets assets_;

  bool is_window_closed_;
  void manageKeys(void);
  void pollEvent(void);

public:
  Game();
  void init(void);
  void mainLoop(void);

  void foo();

  private:
    void drawObjects();
    void moveObjects();
    void gameInit();
};

#endif
