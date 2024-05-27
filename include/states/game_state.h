#pragma once

#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <stack>

class GameStateManager;

class GameState {
protected:
  GameStateManager *state_manager_;

public:
  GameState(GameStateManager *state_manager) : state_manager_(state_manager) {}
  virtual ~GameState() {}
  virtual void handleEvents(SDL_Event &event) = 0;
  virtual void update() = 0;
  virtual void render(SDL_Renderer &renderer) = 0;
  virtual void free() = 0;
};

class GameStateManager {
private:
  std::stack<GameState *> states;

public:
  inline void changeState(GameState *state) {
    if (!states.empty()) {
      states.top()->free();
      states.pop();
    }
    states.push(std::move(state));
  }

  inline void pushState(GameState *state) { states.push(std::move(state)); }

  inline void popState() {
    if (!states.empty()) {
      states.pop();
    }
  }

  inline void handleEvents(SDL_Event &event) {
    if (!states.empty()) {
      states.top()->handleEvents(event);
    }
  }

  inline void update() {
    if (!states.empty()) {
      states.top()->update();
    }
  }

  inline void render(SDL_Renderer &renderer) {
    if (!states.empty()) {
      states.top()->render(renderer);
    }
  }
};
