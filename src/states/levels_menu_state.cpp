#include "states/levels_menu_state.h"
#include "states/game_state.h"
#include "states/level_state.h"
#include "states/state_manager.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <string>

LevelsMenuState::LevelsMenuState(GameStateManager *state_manager_) {
  TTF_Font *font = state_manager_->assets_->getFont();
  SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};
  const int nb_buttons{12};
  const int nb_buttons_row{4};
  const int nb_buttons_column{nb_buttons / nb_buttons_row};

  const double button_width = WINDOW_WIDTH / (2 * nb_buttons_row);
  const double button_height = WINDOW_HEIGHT / (2 * nb_buttons_column + 1);

  std::string text;
  Vector2D position;
  for (int i{0}; i < nb_buttons; ++i) {
    text = std::to_string(i + 1);
    position = Vector2D{button_width * ((i % nb_buttons_row) * 2 + 1),
                        button_height * ((i / nb_buttons_row) * 2 + 1)};

    buttons_.push_back(new Button(position, button_width, button_height, text,
                                  true, white, font, state_manager_,
                                  [text](GameStateManager *state_manager) {
                                    state_manager->changeState(new LevelState(
                                        state_manager, "levels/level_" + text));
                                  }));
  }

  buttons_.push_back(
      new Button(Vector2D{WINDOW_WIDTH / 2,
                          button_height * ((12 / nb_buttons_row) * 2 + 0.5)},
                 3 * button_width, button_height, "Back", true, white, font,
                 state_manager_, [](GameStateManager *state_manager_) -> void {
                   state_manager_->popState();
                 }));
}