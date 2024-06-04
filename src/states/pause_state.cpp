#include "states/pause_state.h"
#include "button.h"
#include "states/game_state.h"
#include "states/main_menu_state.h"
#include "states/menu_state.h"
#include "states/state_manager.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_pixels.h>
#include <SDL_ttf.h>

PauseState::PauseState(GameStateManager *state_manager_, unsigned int score)
    : MenuState(), score_(score) {
  TTF_Font *font = state_manager_->assets_->getFont();
  SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};
  buttons_.push_back(new Button(Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6},
                                WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 12,
                                "PAUSE", false, white, font));

  buttons_.push_back(new Button(
      Vector2D{WINDOW_WIDTH * 2 / 12, WINDOW_HEIGHT * 6 / 12},
      WINDOW_WIDTH * 2 / 12, WINDOW_HEIGHT * 1.5 / 12, "Play", true, white,
      font, state_manager_,
      [](GameStateManager *state_manager) { state_manager->popState(); }));

  buttons_.push_back(new Button(
      Vector2D{WINDOW_WIDTH * 2 / 12, WINDOW_HEIGHT * 8 / 12},
      WINDOW_WIDTH * 2 / 12, WINDOW_HEIGHT * 1.5 / 12, "Menu", true, white,
      font, state_manager_, [](GameStateManager *state_manager) {
        state_manager->changeState(new MainMenuState(state_manager));
      }));

  buttons_.push_back(new Button(
      Vector2D{WINDOW_WIDTH * 2 / 12, WINDOW_HEIGHT * 10 / 12},
      WINDOW_WIDTH * 2 / 12, WINDOW_HEIGHT * 1.5 / 12, "Quit", true, white,
      font, state_manager_,
      [](GameStateManager *state_manager) { state_manager->quit(); }));

  buttons_.push_back(
      new Button(Vector2D{WINDOW_WIDTH * 3 / 4, WINDOW_HEIGHT * 8 / 12},
                 WINDOW_WIDTH * 2 / 12, WINDOW_HEIGHT * 1.5 / 12,
                 "Score: " + std::to_string(score_), false, white, font));
}
