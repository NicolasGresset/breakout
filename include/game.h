#ifndef GAME_H
#define GAME_H

#include "bonus/bonus_manager.h"
#include "collison_engine.h"
#include "grid.h"
#include "gui/SDL2Window.h"
#include "gui/assets.h"
#include "gui/background.h"
#include "gui/menu.h"
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
  std::shared_ptr<SDL2Window> window_ptr_;

  CollisionEngine collision_engine_; // could be unique ptr ?
  std::shared_ptr<Dock> player_;
  std::shared_ptr<Grid> grid_;
  balls_ptr balls_;
  std::shared_ptr<Assets> assets_;

  std::shared_ptr<ElementBackground> background_;
  std::shared_ptr<Button> lifeButton_;
  std::shared_ptr<Button> scoreButton_;

  std::shared_ptr<BonusManager> bonus_manager_;

  unsigned int score_;
  bool is_window_closed_ = false;
  bool is_game_paused_{false};
  void manageKeys(void);
  void pollEvent(void);

  Clock clock_;

  friend class GameController;
  friend class CollisionEngine;

public:
  Game(std::shared_ptr<SDL2Window> &window_ptr);

  // Game(int screen_width, int screen_height);
  /**
   * The main loop of the game
   *
   * return : 1 the game is finished (and the window must be closed)
   *          0 when the current game is finished but the not the window must
   * not be closed
   */
  int mainLoop(void);
  void init(void);

private:
  void drawObjects();
  void drawPauseObjects();
  void moveObjects(Uint64 delta);
  void drawLooseObjects();

public:
  inline std::shared_ptr<Dock> getPlayer() const { return player_; }
  inline std::shared_ptr<BonusManager> getBonusManager() {
    return bonus_manager_;
  }

  // adds a ball at the position of the first ball of the member balls with
  // direction direction
  void addBall(double direction);

  inline bool isLastBall() const { return balls_->size() == 1; }
  inline balls_ptr getBall() const { return balls_; }
  inline void onBrickDestroyed() {
    score_ += 10;
    bonus_manager_->createNewBonus(grid_->getLastDestroyedBrick());
  }
};

#endif
