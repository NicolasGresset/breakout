#include "states/main_menu_state.h"
#include "button.h"
#include "collison_engine.h"
#include "states/game_state.h"
#include "states/level_state.h"
#include "states/levels_menu_state.h"
#include "states/state_manager.h"
#include "utils/constants.h"
#include "utils/utils.h"
#include "utils/vector2D.h"
#include <SDL_pixels.h>

MainMenuState::MainMenuState(GameStateManager *state_manager_) {
  TTF_Font *font = state_manager_->assets_->getFont();
  SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};

  buttons_.push_back(new Button(
      Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6}, WINDOW_WIDTH / 2,
      WINDOW_HEIGHT * 3 / 12, "BREAKOUT", false, white, font, state_manager_));

  buttons_.push_back(new Button(
      Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT * 6 / 12}, WINDOW_WIDTH * 2 / 12,
      WINDOW_HEIGHT * 1.5 / 12, "Play", true, white, font, state_manager_,
      [](GameStateManager *state_manager_) {
        LevelState *level_instance =
            new LevelState(state_manager_, "levels/level_1");
        DEBUG_MSG("Succesfully created a level state instance");
        state_manager_->pushState(level_instance);
      }));

  buttons_.push_back(new Button(
      Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT * 8 / 12}, WINDOW_WIDTH * 2 / 12,
      WINDOW_HEIGHT * 1.5 / 12, "Levels", true, white, font, state_manager_,
      [](GameStateManager *state_manager) {
        state_manager->pushState(new LevelsMenuState(state_manager));
      }));

  buttons_.push_back(new Button(
      Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT * 10 / 12},
      WINDOW_WIDTH * 2 / 12, WINDOW_HEIGHT * 1.5 / 12, "Quit", true, white,
      font, state_manager_,
      [](GameStateManager *state_manager) { state_manager->quit(); }));

  DEBUG_MSG("Main menu succesfully loaded");
}