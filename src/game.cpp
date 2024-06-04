#include "game.h"
#include "states/main_menu_state.h"
#include "utils/utils.h"
#include <SDL_events.h>

Game::Game(int screen_width, int screen_height)
    : SDL2Window(screen_width, screen_height) {
  assets_ = std::make_shared<Assets>(*renderer_);
  state_manager_ = new GameStateManager(screen_width, screen_height, assets_);
}

void Game::run() {
  state_manager_->pushState(new MainMenuState(state_manager_));

  SDL_Event event;
  while (running_) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        DEBUG_MSG("Quitting the game after user demands");
        running_ = false;
      }
      state_manager_->handleEvents(event);
    }
    state_manager_->update();

    clearWindow();
    state_manager_->render(*renderer_);
    update();
    // temporisation ?
  }
}
