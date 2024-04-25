#include "collison_engine.h"
#include "dock.h"
#include "rectangle.h"
#include "rectangle_brick.h"
#include "vector2D.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

CollisionEngine::CollisionEngine(std::vector<Ball> &balls, Grid &grid,
                                 Dock &player)
    : balls_(balls), grid_(grid), player_(player){};

void CollisionEngine::resolveCollisions() {
  for (auto &ball : balls_) {
    if (!ball.bounceIntoWindow(grid_.getWindowHeight(),
                               grid_.getWindowWidth())) {
      // decrement life
    }

    for (auto &brick : grid_.getBricks()) {
      if (isCollisionCircleRect(ball, brick)) {
        ball.bounceOverRectangle(brick);
        brick.decrementLife(1);
        break;
      }
    }

    if (isCollisionCircleRect(ball, (player_))) {
      ball.bounceOverPaddle(player_);
    }
  }
}

// bool CollisionEngine::ballIntersectRectangle(Ball &ball,
//                                              RectangleBrick &brick) const {
//   // We first check if the two Axis Aligned Bounding Box collide
// }

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

  if (distance < ball.getRadius())
    return true;
  return false;
}