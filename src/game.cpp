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

Game::Game()
    : window_(), collision_engine_(), player_(), grid_(), balls_(), assets_(),
      is_window_closed_(false){};

Game::Game(int width, int height, int life)
    : window_(width, height), life_(life) {}


void Game::start() {
  Button button{Vector2D{350, 150}};
  button.draw(window_.getRenderer());
  window_.update();

  window_.temporisation(5000); // todo décommenter en phase finale
  this->mainLoop();
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
  grid_->draw(window_.getRenderer());
  player_->draw(window_.getRenderer());
  for (auto ball : *balls_) {
    ball->draw(window_.getRenderer());
  }
}

void Game::moveObjects(Uint64 delta) {
  player_->move(delta);
  for (auto ball : *balls_) {
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
    collision_engine_->resolveCollisions();
    drawObjects();
    window_.update();
    window_.temporisation(10);
  }
}
