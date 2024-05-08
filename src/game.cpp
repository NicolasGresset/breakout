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
#include <gui/pause.h>

Game::Game(std::shared_ptr<SDL2Window> &window_ptr)
    : window_ptr_(window_ptr), collision_engine_(), player_(), grid_(),
      balls_(), assets_(), score_(0){};

// Game::Game(int width, int height) : window_(width, height) {}

void Game::manageKeys() {
  int nbk;
  const Uint8 *keys = SDL_GetKeyboardState(&nbk);
  if (keys[SDL_SCANCODE_A])
      is_window_closed_ = true; // Marche pas
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

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            is_game_paused_ = !is_game_paused_;

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

  lifeButton_->setText("lives: " + std::to_string(player_->getLifes()));
  lifeButton_->draw(window_ptr_->getRenderer());

  scoreButton_->setText("score: " + std::to_string(score_));
  scoreButton_->draw(window_ptr_->getRenderer());

}

void Game::moveObjects(Uint64 delta) {
  player_->move(delta);
  for (auto ball : *balls_) {
    ball->move(delta);
  }
  background_->update(delta);
}

int Game::mainLoop() {
  while (!is_window_closed_) {
    if (!player_->isAlive()) {
        // Faire l'écran de fin de jeu
        std::cout << "You lost!" << std::endl;
        return 0;
    }

    clock_.tick(); // update the time elapsed since last frame
    window_ptr_->clearWindow();

    pollEvent();
    manageKeys();

    if (is_game_paused_)
    {
        Pause pause{window_ptr_, score_};
        int code = pause.mainLoop();
        // Closing of the window
        if (code == 1)
            break;
        // Return to menu
        if (code == 2)
            return 0;

         is_game_paused_ = !is_game_paused_;
         clock_.tick();
    }
    else
    {
        moveObjects(clock_.time_elapsed);
        if (collision_engine_->resolveCollisions())
            score_ += 10;

        drawObjects();
    }

    window_ptr_->update();
    window_ptr_->temporisation(2);
  }

  return 1;
}
