#include "bonus/bonus.h"
#include "collison_engine.h"
#include "game.h"
#include "object/ball.h"
#include "object/brick.h"
#include "object/dock.h"
#include "object/rectangle.h"
#include "object/rectangle_brick.h"
#include "utils/vector2D.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

CollisionEngine::CollisionEngine(){};

bool CollisionEngine::manageCollisionBrickBall(std::shared_ptr<Brick> brick,
                                               std::shared_ptr<Ball> ball) {
  return false;
}

void CollisionEngine::resolveCollisions(Game &game) {
  for (auto ball : *game.balls_) {
    ball->bounceIntoWindow((*game.grid_).getWindowHeight(),
                           (*game.grid_).getWindowWidth());

    if (ball->isOut() && game.isLastBall()) {
      game.player_->popLife();
      game.player_->reset();
      ball.reset();
    }

    for (auto brick : game.grid_->getBricks()) {
      if (!brick->isDestroyed() && isCollisionCircleRect(*ball, *brick)) {
        ball->bounceOverRectangle(*brick);
        brick->decrementLife(1);
        game.onBrickDestroyed();
        if (brick->isDestroyed()) {
          game.grid_->setLastDestroyedBrick(brick);
          break;
        }
      }
    }

    if (isCollisionCircleRect(*ball, *game.player_)) {
      ball->bounceOverPaddle(*game.player_);
    }
  }
  
  for (auto bonus : game.getBonusManager()->getBonuses()) {
    if (isAABBCollision(*bonus, *game.player_)) {
      if (!bonus->isOut()) {
        bonus->action(game);
        bonus->remove();
        break;
      }

    } else if (isOutofWindow(*bonus, game.grid_->getWindowWidth(),
                             game.grid_->getWindowHeight())) {

      bonus->remove();
    }
  }
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

  float left1 = rectangle1.getPosition().x_ - rectangle1.getWidth() / 2;
  float right1 = rectangle1.getPosition().x_ + rectangle1.getWidth() / 2;
  float top1 = rectangle1.getPosition().y_ + rectangle1.getHeight() / 2;
  float bottom1 = rectangle1.getPosition().y_ - rectangle1.getHeight() / 2;

  float left2 = rectangle2.getPosition().x_ - rectangle2.getWidth() / 2;
  float right2 = rectangle2.getPosition().x_ + rectangle2.getWidth() / 2;
  float top2 = rectangle2.getPosition().y_ + rectangle2.getHeight() / 2;
  float bottom2 = rectangle2.getPosition().y_ - rectangle2.getHeight() / 2;

  // Vérifier si les rectangles se chevauchent sur chaque axe
  bool overlapX = (left1 <= right2) && (right1 >= left2);
  bool overlapY = (bottom1 <= top2) && (top1 >= bottom2);

  // Si les rectangles se chevauchent sur les deux axes, il y a une collision
  return overlapX && overlapY;
}
