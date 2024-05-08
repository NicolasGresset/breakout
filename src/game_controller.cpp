#include "game_controller.h"
#include "collison_engine.h"
#include "game.h"
#include "object/ball.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_render.h>
#include <memory>

void GameController::init(std::shared_ptr<SDL2Window> & window_ptr, int screen_width, int screen_height, int life) {
  game_ = std::make_shared<Game>(window_ptr);
  game_->assets_ = std::make_shared<Assets>(game_->window_ptr_->getRenderer());
  game_->grid_ = std::make_shared<Grid>(10, 8, screen_width, screen_height,
                                        game_->assets_);
  game_->player_ = std::make_shared<Dock>(
      Vector2D(static_cast<double>(screen_width) / 2,
               static_cast<double>(screen_height - PADDING) -
                   static_cast<double>(DOCK_HEIGHT) / 2),
      DOCK_WIDTH, DOCK_HEIGHT,
      game_->assets_->getRectangleTexture(Color::blue),
      Vector2D(0, 0), life);
  game_->balls_ = std::make_shared<std::vector<std::shared_ptr<Ball>>>();
  game_->balls_->push_back(std::make_shared<Ball>(
      Vector2D(INITIAL_BALL_POSITION_X, INITIAL_BALL_POSITION_Y),
      game_->assets_->getBallTexture(Color::blue), Vector2D(0, BALL_SPEED_NORM),
      BALL_RADIUS));

  game_->collision_engine_ = std::make_shared<CollisionEngine>(
      game_->balls_, game_->grid_, game_->player_);

  game_->background_ = std::make_shared<ElementBackground>(
      game_->assets_->getBackgroundTexture(), screen_width, screen_height);

  std::string life_text = "lives: " + std::to_string(life);
  game_->lifeButton_ = std::make_shared<Button>(
      Vector2D{screen_width - 80., screen_height - 40.},
      80, 30, life_text, false);

  std::string score_text = "score: 0";
  game_->scoreButton_ = std::make_shared<Button>(
      Vector2D{80., screen_height - 40.}, 80, 30, score_text, false);

}
