#include "game.h"
#include "collison_engine.h"
#include "grid.h"
#include "gui/background.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <iostream>

Game::Game(std::shared_ptr<SDL2Window> &window_ptr)
    : window_ptr_(window_ptr), collision_engine_(), player_(), grid_(),
      balls_(), assets_(){};

// Game::Game(int width, int height) : window_(width, height) {}

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
        // Mettre en pause par un booléen
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
  background_->draw(window_ptr_->getRenderer());
  grid_->draw(window_ptr_->getRenderer());
  player_->draw(window_ptr_->getRenderer());
  for (auto ball : *balls_) {
    ball->draw(window_ptr_->getRenderer());
  }
}

void Game::moveObjects(Uint64 delta) {
  player_->move(delta);
  for (auto ball : *balls_) {
    ball->move(delta);
  }
  background_->update(delta);
}

void Game::mainLoop() {
  while (!is_window_closed_) {
    if (!player_->isAlive()) {
        // Faire l'écran de fin de jeu
        std::cout << "You lost!" << std::endl;
        break;
    }


    clock_.tick(); // update the time elapsed since last frame
    window_ptr_->clearWindow();
    pollEvent();
    manageKeys();
    moveObjects(clock_.time_elapsed);
    collision_engine_->resolveCollisions();
    drawObjects();
    window_ptr_->update();
    window_ptr_->temporisation(2);
  }
}
