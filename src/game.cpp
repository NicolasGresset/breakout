#include "game.h"
#include "bonus/bonus.h"
#include "collison_engine.h"
#include "grid.h"
#include "gui/SDL2Window.h"
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

Game::Game(int screen_width, int screen_height) : SDL2Window(screen_width, screen_height), score_(0) {}



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
  grid_->draw(*renderer_);
  player_->draw(*renderer_);
  for (auto ball : *balls_) {
    ball->draw(*renderer_);
  }

  lifeButton_->setText("lives: " + std::to_string(player_->getLifes()));
  lifeButton_->draw(*renderer_);

  scoreButton_->setText("score: " + std::to_string(score_));
  scoreButton_->draw(*renderer_);

  for (auto bonus : bonus_manager_->getBonuses()) {
    bonus->draw(*renderer_);
  }
}

bool Game::isGameEnded() const {
  int number = 0;
  for (auto brick : grid_->getBricks()) {
    if (!brick->isDestroyed()) {
      number++;
    }
  }
  return number == 0;
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

  std::vector<std::shared_ptr<Brick>> bricks = grid_->getBricks();
  for (auto brick = bricks.begin(); brick != bricks.end();) {
    if ((*brick)->isDestroyed()) {
      brick = bricks.erase(brick);
    } else {
      brick++;
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

  loose_text_countour.draw(*renderer_);
  loose_text.draw(*renderer_);
  score_text.draw(*renderer_);
}

void Game::drawWinObjects() {

  Button win_text_countour{
      Vector2D{WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 6 - 5},
      WINDOW_WIDTH / 2 + 15,
      WINDOW_HEIGHT * 3 / 12 + 15,
      "You won",
      false,
      {0xFF, 0xFF, 0xFF, 0x00}};

  Button win_text{Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 6},
                  WINDOW_WIDTH / 2,
                  WINDOW_HEIGHT * 3 / 12,
                  "You won",
                  false,
                  {0x20, 0x20, 0xF0, 0x00}};

  Button score_text{Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2},
                    WINDOW_WIDTH / 3, WINDOW_HEIGHT * 3 / 12,
                    "Score: " + std::to_string(score_), false};

  win_text_countour.draw(*renderer_);
  win_text.draw(*renderer_);
  score_text.draw(*renderer_);
}

int Game::mainLoop() {
  while (!is_window_closed_) {
    clock_.tick(); // update the time elapsed since last frame
    bonus_manager_->loop(clock_.time_elapsed);
    if (!player_->isAlive()) {
      // Faire l'écran de fin de jeu
      // std::cout << "You lost!" << std::endl;
      drawLooseObjects();

      update();
      temporisation(3000);
      return 0;
    }

    clearWindow();

    pollEvent();
    manageKeys();

    if (is_game_paused_) {
      Pause pause{window_, score_};
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
      if (isGameEnded()) {
        drawWinObjects();

        update();
        temporisation(3000);
        return 0;
      }
      drawObjects();
    }

    update();
    temporisation(3);
  }

  return 1;
}
