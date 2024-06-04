#pragma once

#include "utils/clock.h"
#include <SDL2/SDL.h>
#include <SDL_render.h>

class GameStateManager;

class GameState {
protected:
  Clock clock_;

public:
  GameState() {}
  virtual ~GameState() {}
  virtual void handleEvents(SDL_Event &event,
                            GameStateManager *state_manager) = 0;
  virtual void update(GameStateManager *state_manager) = 0;
  virtual void render(SDL_Renderer &renderer) = 0;
  virtual void free() = 0;
};
