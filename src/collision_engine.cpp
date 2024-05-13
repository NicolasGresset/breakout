#include "bonus/bonus.h"
#include "collison_engine.h"
#include "game.h"
#include "object/dock.h"
#include "object/rectangle.h"
#include "object/rectangle_brick.h"
#include "utils/vector2D.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

CollisionEngine::CollisionEngine() : balls_(), grid_(), player_(){};

CollisionEngine::CollisionEngine(
    balls_ptr balls, std::shared_ptr<Grid> grid, std::shared_ptr<Dock> player,
    std::shared_ptr<std::vector<std::shared_ptr<Bonus>>> bonuses)
    : balls_(balls), grid_(grid), player_(player), bonuses_(bonuses){};

bool CollisionEngine::resolveCollisions(Game &game) {
  bool return_code = false;
  for (auto ball : *balls_) {
    if (!ball->bounceIntoWindow((*grid_).getWindowHeight(),
                                (*grid_).getWindowWidth())) {
      player_->popLife();
      player_->reset();
    }

    for (auto brick : (grid_.get())->getBricks()) {
      if (!brick->isDestroyed() && isCollisionCircleRect(*ball, *brick)) {
        ball->bounceOverRectangle(*brick);
        brick->decrementLife(1);
        if (brick->isDestroyed()) {
          grid_->setLastDestroyedBrick(brick);
        }
        return_code = true;
        break;
      }
    }

    if (isCollisionCircleRect(*ball, *player_)) {
      ball->bounceOverPaddle(*player_);
    }

    for (auto bonus : game.getBonusManager()->getBonuses()) {
      if (isAABBCollision(*bonus, *player_)) {
        if (!bonus->isOut())
          bonus->action(game);
      } else if (isOutofWindow(*bonus, grid_->getWindowWidth(),
                               grid_->getWindowHeight())) {

        bonus->remove();
      }
    }
  }
  return return_code;
}

bool CollisionEngine::isOutofWindow(Rectangle &rectangle, int width,
                                    int height) {
  return (rectangle.getPosition().x_ + rectangle.getWidth() / 2 > width ||
          rectangle.getPosition().x_ - rectangle.getWidth() / 2 < 0 ||
          rectangle.getPosition().y_ + rectangle.getHeight() / 2 > height ||
          rectangle.getPosition().y_ - rectangle.getHeight() / 2 < 0);
}

bool CollisionEngine::isCollisionCircleRect(Ball &ball,
                                            Rectangle &rectangle) const {
  Vector2D ball_position = ball.getPosition();
  Vector2D rectangle_position = rectangle.toUpperLeftCoords();

  double test_x{ball_position.x_};
  double test_y{ball_position.y_};

  if (ball_position.x_ < rectangle_position.x_) {
    test_x = rectangle_position.x_;

  } else if (ball_position.x_ > rectangle_position.x_ + rectangle.getWidth()) {
    test_x = rectangle_position.x_ + rectangle.getWidth();
  }

  if (ball_position.y_ < rectangle_position.y_) {
    test_y = rectangle_position.y_;

  } else if (ball_position.y_ > rectangle_position.y_ + rectangle.getHeight()) {
    test_y = rectangle_position.y_ + rectangle.getHeight();
  }

  double distance =
      pow(ball_position.x_ - test_x, 2) + pow(ball_position.y_ - test_y, 2);

  return (distance < ball.getRadius());
}

bool CollisionEngine::isAABBCollision(Rectangle &rectangle1,
                                      Rectangle &rectangle2) {
  return !(rectangle1.getPosition().x_ + rectangle1.getWidth() / 2 <
               rectangle2.getPosition().x_ - rectangle2.getWidth() / 2 ||
           rectangle1.getPosition().x_ - rectangle1.getWidth() / 2 <
               rectangle2.getPosition().x_ + rectangle2.getWidth() / 2 ||
           rectangle1.getPosition().y_ + rectangle1.getHeight() / 2 <
               rectangle2.getPosition().y_ - rectangle2.getHeight() / 2 ||
           rectangle1.getPosition().y_ - rectangle1.getHeight() / 2 <
               rectangle2.getPosition().y_ + rectangle2.getHeight() / 2);
}