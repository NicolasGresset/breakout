#include "states/win_level_state.h"
#include "states/game_state.h"
#include "states/main_menu_state.h"
#include "states/state_manager.h"
#include "utils/constants.h"
#include <SDL_events.h>

WinLevelState::WinLevelState(GameStateManager *state_manager_, int score)
    : MenuState() {
  TTF_Font *font = state_manager_->assets_->getFont();
  SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};
  buttons_.push_back(
      new Button(Vector2D{WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 6 - 5},
                 WINDOW_WIDTH / 2 + 15, WINDOW_HEIGHT * 3 / 12 + 15, "You won",
                 false, white, font));
  buttons_.push_back(new Button(Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6},
                                WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3 / 12,
                                "You won", false, white, font));
  buttons_.push_back(new Button(Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
                                WINDOW_WIDTH / 3, WINDOW_HEIGHT * 3 / 12,
                                "Score: " + std::to_string(score), false, white,
                                font));
}

void WinLevelState::update(GameStateManager *state_manager) {
  clock_.tick();
  if (clock_.getTotalTime() > 3000) {
    state_manager->changeState(new MainMenuState(state_manager));
  }
}
