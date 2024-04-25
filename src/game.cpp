#include "../include/game.h"
#include "../include/button.h"
#include "collison_engine.h"
#include "color.h"
#include "grid.h"
#include <SDL_events.h>
#include <SDL_ttf.h>

Game::Game()
    : collision_engine_(balls_, grid_, player_), grid_(&assets_),
      is_window_closed_(false) {
  balls_.push_back(Ball());
};


void Game::init()
{
    window_.init();
    renderer_ = window_.getRenderer();
    window_.update();

    Button button{Vector2D{350, 150}};
    button.draw(renderer_);
    window_.update();

    window_.temporisation(5000);

    gameInit();
}



void Game::gameInit() {
    window_.update();
    assets_.loadTextures(renderer_);
    grid_.init();
    player_.setTexture(assets_.getRectangleTexture(Color::blue));
    balls_[0].setTexture(assets_.getBallTexture(Color::blue));
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
        player_.handleEvent(event);
      break;
    }
  }
  return;
}

void Game::foo() {
  SDL_Rect destinationRect = {100, 100, 70, 70}; // x, y, width, height
  SDL_RenderClear(renderer_);
  SDL_RenderCopy(renderer_, assets_.getRectangleTexture(Color::blue), NULL,
                 &destinationRect);
}

void Game::drawObjects() {
  grid_.draw(renderer_);
  player_.draw(renderer_);
  for (auto &ball : balls_) {
    ball.draw(renderer_);
  }
}

void Game::moveObjects() {
  player_.move();
  for (auto &ball : balls_) {
    ball.move();
  }
}

void Game::mainLoop() {
  while (!is_window_closed_) {
    window_.clearWindow();
    this->pollEvent();
    this->manageKeys();
    moveObjects();
    collision_engine_.resolveCollisions();
    drawObjects();
    window_.update();
    window_.temporisation(50);
  }
}
