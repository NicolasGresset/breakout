#include "states/menu_state.h"
#include "button.h"
#include "states/game_state.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <vector>

MenuState::MenuState() : GameState() {}

void MenuState::handleEvents(SDL_Event &event,
                             GameStateManager *state_manager) {
  (void)state_manager;
  for (auto button : buttons_) {
    button->handleEvents(event);
  }
}

void MenuState::update(GameStateManager *state_manager) {
  (void)state_manager;
  for (auto button : buttons_) {
    button->update();
  }
}

void MenuState::render(SDL_Renderer &renderer) {

  // todo : draw random noise
  for (auto button : buttons_) {
    button->draw(renderer);
  }
}

void MenuState::free() {
  // todo
}