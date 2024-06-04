#pragma once

#include "button.h"
#include "gui/assets.h"
#include "states/game_state.h"
#include <memory>
#include <vector>

/**
 * @brief An abstract class representing a menu with buttons
 *
 */
class MenuState : public GameState {
protected:
  std::vector<Button *> buttons_;

public:
  MenuState();
  void handleEvents(SDL_Event &events,
                    GameStateManager *state_manager) override;
  void update(GameStateManager *state_manager) override;
  void render(SDL_Renderer &renderer) override;
  void free() override;

  inline void resume() override {}
};
