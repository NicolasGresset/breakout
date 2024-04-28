#include "game.h"
#include "button.h"
#include "collison_engine.h"
#include "grid.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>
#include <iostream>

Game::Game()
    : window_(), collision_engine_(), player_(), grid_(), balls_(), assets_(),
      is_window_closed_(false){};

void Game::init() {
  window_.init();
  window_.update();

#ifndef GAME_TESTING
  Button button{Vector2D{350, 150}};
  button.draw(window_.getRenderer());
#endif
  window_.update();

  window_.temporisation(1000); // todo décommenter en phase finale
  //gameInit();

}

void Game::gameInit() {
  window_.update();
  assets_.loadTextures(window_.getRenderer());
  grid_.init();
  // player_ = Dock(
  //     Vector2D(WINDOW_WIDTH / 2, WINDOW_HEIGHT - PADDING - DOCK_HEIGHT / 2),
  //     DOCK_WIDTH, DOCK_HEIGHT, assets_.getRectangleTexture(Color::blue),
  //     Vector2D(DOCK_SPEED_X, 0));
  player_->getPosition().print();
  player_->setTexture(assets_.getRectangleTexture(Color::blue));
  balls_[0]->setTexture(assets_.getBallTexture(Color::blue));
}

void Game::manageKeys() {
  int nbk;
  const Uint8 *keys = SDL_GetKeyboardState(&nbk);
  if (keys[SDL_SCANCODE_ESCAPE])
    is_window_closed_ = true;
}

void Game::pollEvent() {
  SDL_Event event;
  while (!is_window_closed_ && SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      is_window_closed_ = true;
      break;

    default:
      if (!event.key.repeat)
        player_->handleEvent(event);
      break;
    }
  }
  return;
}

void Game::drawObjects() {
  grid_.draw(window_.getRenderer());
  player_->draw(window_.getRenderer());
  for (auto &ball : balls_) {
    ball->draw(window_.getRenderer());
  }
}

void Game::moveObjects(Uint64 delta) {
  player_->move(delta);
  for (auto &ball : balls_) {
    ball->move(delta);
  }
}

void Game::mainLoop() {
  while (!is_window_closed_) {
    clock_.tick(); // update the time elapsed since last frame
    window_.clearWindow();
    this->pollEvent();
    this->manageKeys();
    moveObjects(clock_.time_elapsed);
    collision_engine_.resolveCollisions();
    drawObjects();
    window_.update();
    window_.temporisation(150);
  }
}
