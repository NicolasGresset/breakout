#pragma once

#include "states/menu_state.h"

class PauseState : public MenuState {
private:
  unsigned int score_;

public:
  PauseState(GameStateManager *state_manager, unsigned int score);
};