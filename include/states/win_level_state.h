#pragma once

#include "states/menu_state.h"

class WinLevelState : public MenuState {
public:
  WinLevelState(GameStateManager *state_manager, int score);
  void update(GameStateManager *state_manager) override;
};