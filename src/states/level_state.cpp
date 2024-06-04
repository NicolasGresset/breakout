#include "states/level_state.h"
#include "collison_engine.h"
#include "grid.h"
#include "object/dock.h"
#include "states/game_state.h"
#include "states/pause_state.h"
#include "states/state_manager.h"
#include "states/win_level_state.h"
#include "utils/constants.h"
#include "utils/utils.h"

LevelState::LevelState(GameStateManager *state_manager_, std::string level_path)
    : GameState() {
  printf("hey ! \n");
  DEBUG_MSG("Entering levelstate instance constructor");
  grid_ = std::make_shared<Grid>(10, 3, state_manager_->screen_width_,
                                 state_manager_->screen_height_,
                                 state_manager_->assets_, level_path);
  DEBUG_MSG("Succesfully created the grid");
  player_ = std::make_shared<Dock>(
      Vector2D(static_cast<double>(state_manager_->screen_width_) / 2,
               static_cast<double>(state_manager_->screen_height_ - PADDING) -
                   static_cast<double>(DOCK_HEIGHT) / 2),
      DOCK_WIDTH, DOCK_HEIGHT,
      state_manager_->assets_->getRectangleTexture(Color::blue), Vector2D(0, 0),
      INITIAL_PLAYER_LIFE);
  balls_ = std::make_shared<std::vector<std::shared_ptr<Ball>>>();
  balls_->push_back(std::make_shared<Ball>(
      Vector2D(INITIAL_BALL_POSITION_X, INITIAL_BALL_POSITION_Y),
      state_manager_->assets_->getBallTexture(Color::blue),
      Vector2D(0, BALL_SPEED_NORM), BALL_RADIUS));

  bonus_manager_ = std::make_shared<BonusManager>(
      state_manager_->assets_->getBonusesTextures(), BONUS_INTERVAL_RATE);

  DEBUG_MSG("Succesfully created bonus manager");

  TTF_Font *font = state_manager_->assets_->getFont();
  DEBUG_MSG("accessing font");
  printf("font = %p\n", font);
  DEBUG_MSG("succesfully accessed font");
  SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};
  life_button_ = std::make_shared<Button>(
      Vector2D{state_manager_->screen_width_ - 80.,
               state_manager_->screen_height_ - 40.},
      80, 30, "lives: " + std::to_string(INITIAL_PLAYER_LIFE), false, white,
      font);

  DEBUG_MSG("Created life_button");
  std::string score_text = "score: 0";
  score_button_ = std::make_shared<Button>(
      Vector2D{80., state_manager_->screen_height_ - 40.}, 80, 30, score_text,
      false, white, font);
  DEBUG_MSG("Succesfully created the level state");
}

void LevelState::handleEvents(SDL_Event &event,
                              GameStateManager *state_manager_) {
  switch (event.type) {
  case SDL_QUIT:
    state_manager_->quit();
    break;

  default:
    if (!event.key.repeat)
      player_->handleEvent(event);

    if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
      state_manager_->pushState(new PauseState(state_manager_, score_));
  }
}

void LevelState::update(GameStateManager *state_manager_) {
  clock_.tick();
  moveObjects(clock_.time_elapsed);
  CollisionEngine::resolveCollisions(*this);
  garbageCollector();

  // todo : understand buttons
  life_button_->setText("lives: " + std::to_string(player_->getLifes()));
  score_button_->setText("score: " + std::to_string(score_));
  if (isGameWon()) {
    state_manager_->changeState(new WinLevelState(state_manager_, score_));
  }
}

void LevelState::render(SDL_Renderer &renderer) {
  grid_->draw(renderer);
  player_->draw(renderer);
  for (auto ball : *balls_) {
    ball->draw(renderer);
  }

  life_button_->draw(renderer);
  score_button_->draw(renderer);

  for (auto bonus : bonus_manager_->getBonuses()) {
    bonus->draw(renderer);
  }
}

void LevelState::free() {
  // todo
}

void LevelState::moveObjects(Uint64 delta) {
  player_->move(delta);

  for (auto ball : *balls_) {
    ball->move(delta);
  }

  std::vector<std::shared_ptr<Bonus>> bonuses = bonus_manager_->getBonuses();
  for (auto bonus : bonuses) {
    bonus->move(delta);
  }
}

bool LevelState::isGameWon() const {
  int number = 0;
  for (auto brick : grid_->getBricks()) {
    if (!brick->isDestroyed()) {
      number++;
    }
  }
  return number == 0 && player_->getLifes() > 0;
}

void LevelState::onBrickDestroyed() {
  score_ += 10;
  bonus_manager_->createNewBonus(grid_->getLastDestroyedBrick());
}

void LevelState::garbageCollector() {
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


// todo complete
void LevelState::addBall(double direction) {
  Vector2D speed(BALL_SPEED_NORM * cos(direction),
                 BALL_SPEED_NORM * sin(direction));
  // balls_->push_back(std::make_shared<Ball>(balls_->at(0)->getPosition(),
  //                                          assets_->getBallTexture(Color::blue),
  //                                          speed, BALL_RADIUS));
}
