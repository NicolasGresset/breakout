#include "game.h"
#include "bonus/bonus.h"
#include "collison_engine.h"
#include "grid.h"
#include "gui/background.h"
#include "gui/color.h"
#include "object/ball.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <gui/pause.h>
#include <iostream>
#include <memory>

Game::Game(std::shared_ptr<SDL2Window> &window_ptr)
    : window_ptr_(window_ptr), collision_engine_(), player_(), grid_(),
      balls_(), assets_(), score_(0){};

// Game::Game(int width, int height) : window_(width, height) {}

void Game::addBall(double direction) {
  Vector2D speed(BALL_SPEED_NORM * cos(direction),
                 BALL_SPEED_NORM * sin(direction));
  balls_->push_back(std::make_shared<Ball>(balls_->at(0)->getPosition(),
                                           assets_->getBallTexture(Color::blue),
                                           speed, BALL_RADIUS));
}

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
  // background_->draw(window_ptr_->getRenderer());
  grid_->draw(window_ptr_->getRenderer());
  player_->draw(window_ptr_->getRenderer());
  for (auto ball : *balls_) {
    ball->draw(window_ptr_->getRenderer());
  }

  lifeButton_->setText("lives: " + std::to_string(player_->getLifes()));
  lifeButton_->draw(window_ptr_->getRenderer());

  scoreButton_->setText("score: " + std::to_string(score_));
  scoreButton_->draw(window_ptr_->getRenderer());

  for (auto bonus : bonus_manager_->getBonuses()) {
    bonus->draw(window_ptr_->getRenderer());
  }
}

void Game::garbageCollector() {
  for (auto ball = balls_->begin(); ball != balls_->end();) {
    if ((*ball)->isOut()) {
      ball = balls_->erase(ball);
    } else {
      ball++;
    }
  }

  std::vector<std::shared_ptr<Bonus>> bonuses = bonus_manager_->getBonuses();
  for (auto bonus = bonuses.begin(); bonus != bonuses.end();) {
    if ((*bonus)->isOut()) {
      bonus = bonuses.erase(bonus);
    } else {
      bonus++;
    }
  }
}
void Game::moveObjects(Uint64 delta) {
  player_->move(delta);

  for (auto ball : *balls_) {
    ball->move(delta);
  }

  std::vector<std::shared_ptr<Bonus>> bonuses = bonus_manager_->getBonuses();
  for (auto bonus : bonuses) {
    bonus->move(delta);
  }
}

void Game::drawLooseObjects() {

  Button loose_text_countour{
      Vector2D{WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 6 - 5},
      WINDOW_WIDTH / 2 + 20,
      WINDOW_HEIGHT * 3 / 12 + 20,
      "You lost",
      false,
      {0x00, 0x00, 0x00, 0x00}};

  Button loose_text{Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6},
                    WINDOW_WIDTH / 2,
                    WINDOW_HEIGHT * 3 / 12,
                    "You lost",
                    false,
                    {0xF0, 0x20, 0x20, 0x00}};

  Button score_text{Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
                    WINDOW_WIDTH / 3, WINDOW_HEIGHT * 3 / 12,
                    "Score: " + std::to_string(score_), false};

  loose_text_countour.draw(window_ptr_->getRenderer());
  loose_text.draw(window_ptr_->getRenderer());
  score_text.draw(window_ptr_->getRenderer());
}
int Game::mainLoop() {
  while (!is_window_closed_) {
    clock_.tick(); // update the time elapsed since last frame
    bonus_manager_->loop(clock_.time_elapsed);
    if (!player_->isAlive()) {
      // Faire l'écran de fin de jeu
      // std::cout << "You lost!" << std::endl;
      drawLooseObjects();

      window_ptr_->update();
      window_ptr_->temporisation(3000);
      return 0;
    }

    window_ptr_->clearWindow();

    pollEvent();
    manageKeys();

    if (is_game_paused_) {
      Pause pause{window_ptr_, score_};
      int code = pause.mainLoop();
      // Closing of the window
      if (code == 1)
        break;
      // Return to menu
      if (code == 2)
        return 0;

      is_game_paused_ = false;
      clock_.tick();
    } else {
      moveObjects(clock_.time_elapsed);
      garbageCollector();
      collision_engine_.resolveCollisions(*this);

      drawObjects();
    }

    window_ptr_->update();
    window_ptr_->temporisation(3);
  }

  return 1;
}
