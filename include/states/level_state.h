#pragma once
#include "bonus/bonus.h"
#include "bonus/bonus_manager.h"
#include "button.h"
#include "collison_engine.h"
#include "gui/assets.h"
#include "object/ball.h"
#include "object/dock.h"
#include "states/game_state.h"
#include <memory>

class Dock;
class Grid;
class BonusManager;
class Assets;

/**
 * @brief Refers to a level being actually played by the user
 *
 */
class LevelState : public GameState {
  friend class CollisionEngine;

private:
  std::shared_ptr<Dock> player_;
  std::shared_ptr<Grid> grid_;
  balls_ptr balls_;
  unsigned int score_;

  std::shared_ptr<BonusManager> bonus_manager_;

  std::shared_ptr<Button> life_button_;
  std::shared_ptr<Button> score_button_;

public:
  void handleEvents(SDL_Event &events,
                    GameStateManager *state_manager) override;
  void update(GameStateManager *state_manager) override;
  void render(SDL_Renderer &renderer) override;
  void free() override;

private:
  void moveObjects(const Uint64 delta);
  void garbageCollector(); // todo make it work
  bool isGameWon() const;  // todo improve this function

public:
  LevelState(GameStateManager *state_manager_,
             std::string level_path = "levels/level_1");
  void onBrickDestroyed();
  inline bool isLastBall() const { return balls_->size() == 1; }
  inline BonusManager &getBonusManager() const { return *bonus_manager_; }

  inline void addLives(int number) { player_->addLives(number); }
  inline balls_ptr getBalls(void) { return balls_; }
  // adds a ball at the position of the first ball of the member balls with
  // direction direction
  void addBall(double direction);
};