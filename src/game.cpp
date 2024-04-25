#include "game.h"
#include "button.h"
#include "collison_engine.h"
#include "gui/color.h"
#include "utils/constants.h"
#include "grid.h"
#include <SDL_events.h>
#include <SDL_ttf.h>
#include <SDL_timer.h>

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

    // window_.temporisation(5000); // todo décommenter en phase finale

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

void Game::drawObjects() {
  grid_.draw(renderer_);
  player_.draw(renderer_);
  for (auto &ball : balls_) {
    ball.draw(renderer_);
  }
}

void Game::moveObjects(Uint64 delta) {
  player_.move(delta);
  for (auto &ball : balls_) {
    ball.move(delta);
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
    window_.temporisation(15);
  }
}
