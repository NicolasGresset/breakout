#pragma once

#include "states/menu_state.h"

class LooseLevelState : public MenuState {
public:
  LooseLevelState(GameStateManager *state_manager, int score);
};