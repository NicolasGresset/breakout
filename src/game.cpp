#include "../include/game.h"
#include "color.h"

Game::Game() : is_window_closed_(false), grid_(&assets_){};

void Game::init() {
  window_.init();
  renderer_ = window_.getRenderer();
  assets_.loadTextures(renderer_);
  grid_.init();
  player_.setTexture(assets_.getRectangleTexture(Color::blue));
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

void Game::mainLoop() {
  while (!is_window_closed_) {

    this->pollEvent();
    this->manageKeys();
    grid_.draw(renderer_);
    player_.draw(renderer_);
    window_.update();
    window_.temporisation(100);
  }
}