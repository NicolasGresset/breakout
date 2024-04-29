#include "game.h"
#include "collison_engine.h"
#include "grid.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_timer.h>
#include <iostream>

Game::Game()
    : window_(), collision_engine_(), player_(), grid_(), balls_(), assets_(),
      is_window_closed_(false){};

Game::Game(int width, int height, int life)
    : window_(width, height), life_(life) {}



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

void Game::gameMainLoop() {
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

void Game::menuMainLoop() {
    int mouseX, mouseY;
    bool play = false;

    while (!is_window_closed_) {
        clock_.tick(); // update the time elapsed since last frame
        window_.clearWindow();

#ifndef GAME_TESTING

        Button breakout_text{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT/6},  WINDOW_WIDTH/2, WINDOW_HEIGHT*3/12};
        breakout_text.draw(window_.getRenderer());

        Button play_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*6/12},
            WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, { 0x00, 0x00, 0xFF, 0xFF }, "Play"};
        play_button.draw(window_.getRenderer());

        Button levels_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*8/12},
            WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, { 0x00, 0x00, 0xFF, 0xFF }, "Levels"};
        levels_button.draw(window_.getRenderer());

        Button quit_button{Vector2D{WINDOW_WIDTH/2, WINDOW_HEIGHT*10/12},
            WINDOW_WIDTH*2/12, WINDOW_HEIGHT*1.5/12, { 0x00, 0x00, 0xFF, 0xFF }, "Quit"};
        quit_button.draw(window_.getRenderer());

        SDL_GetMouseState(&mouseX, &mouseY);
        if (quit_button.isClicked(mouseX, mouseY)) {
            std::cout << mouseX << " " << mouseY << std::endl;
            //is_window_closed_ = true;
        }
        else if (play_button.isClicked(mouseX, mouseY))
        {
            play = true;
            break;
        }

#endif
        this->pollEvent();
        this->manageKeys();

        window_.update();
        window_.temporisation(50);

        if (play)
        {
            gameMainLoop();
        }
    }
}
