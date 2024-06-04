#pragma once

#include "game_state.h"
#include "gui/assets.h"
#include <stack>

class GameStateManager {
private:
  std::stack<GameState *> states;

public:
  const int screen_width_;
  const int screen_height_;
  std::shared_ptr<Assets> assets_;

public:
  inline GameStateManager(int screen_width, int screen_height,
                          std::shared_ptr<Assets> assets)
      : screen_width_(screen_width), screen_height_(screen_height),
        assets_(assets) {}

  inline void changeState(GameState *state) {
    popState();
    pushState(state);
  }

  inline void pushState(GameState *state) {
    states.push(std::move(state));
  }

  inline void popState() {
    if (!states.empty()) {
      states.top()->free();
      states.pop();
      if (!states.empty()) {
        states.top()->resume();
      }
    }
  }

  // gracefully exits all states
  inline void quit() {
    while (!states.empty()) {
      popState();
    }
  }

  inline void handleEvents(SDL_Event &event) {
    if (!states.empty()) {
      states.top()->handleEvents(event, this);
    }
  }

  inline void update() {
    if (!states.empty()) {
      states.top()->update(this);
    }
  }

  inline void render(SDL_Renderer &renderer) {
    if (!states.empty()) {
      states.top()->render(renderer);
    }
  }
};
