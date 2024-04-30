#ifndef GAME_H
#define GAME_H

#include "button.h"
#include "collison_engine.h"
#include "grid.h"
#include "gui/SDL2Window.h"
#include "gui/assets.h"
#include "gui/background.h"
#include "object/ball.h"
#include "object/dock.h"
#include "utils/clock.h"
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <SDL_timer.h>
#include <memory>

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

A game i
s parametrized by the type of bricks it is composed : either rectangles
or hexagons

*/

// template<typename T>
class Game {
private:
  SDL2Window window_;

  std::shared_ptr<CollisionEngine> collision_engine_; // could be unique ptr ?
  std::shared_ptr<Dock> player_;
  std::shared_ptr<Grid> grid_;
  balls_ptr balls_;
  std::shared_ptr<Assets> assets_;

  std::shared_ptr<Background> background_;

  bool is_window_closed_ = false;
  void manageKeys(void);
  void pollEvent(void);

  Clock clock_;

  friend class GameController;

public:
  Game();

  Game(int screen_width, int screen_height);
  void mainLoop(void);
  void init(void);
  void gameMainLoop(void);
  void menuMainLoop(void);

private:
  void drawObjects();
  void moveObjects(Uint64 delta);
};

#endif
