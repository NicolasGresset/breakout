#include "bonus/bonus.h"
#include "collison_engine.h"
#include "game.h"
#include "object/ball.h"
#include "object/brick.h"
#include "object/dock.h"
#include "object/line.h"
#include "object/rectangle.h"
#include "object/rectangle_brick.h"
#include "object/triangle_brick.h"
#include "utils/direction.h"
#include "utils/vector2D.h"
#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

CollisionEngine::CollisionEngine(){};

void CollisionEngine::manageCollisionBrickBall(std::shared_ptr<Brick> brick,
                                               std::shared_ptr<Ball> ball,
                                               Game &game) {
  if (brick->isDestroyed()) {
    return;
  }

  Direction normal = brick->isCollisionCircle(*ball);
  if (normal.isValid()) {
    ball->bounceOverLine(normal);
    brick->decrementLife(1);

    if (brick->isDestroyed()) {
      game.grid_->setLastDestroyedBrick(brick);
      game.onBrickDestroyed();
    }
  }
}

Direction CollisionEngine::checkCollision(Ball &ball, RectangleBrick &brick) {
  Rectangle rectangle = static_cast<Rectangle>(brick);
  return checkCollision(ball, rectangle);
}

Direction CollisionEngine::checkCollision(Ball &ball, TriangleBrick &brick) {
  Triangle triangle = static_cast<Triangle>(brick);
  return checkCollision(ball, triangle);
}

void CollisionEngine::resolveCollisions(Game &game) {
  for (auto ball : *game.balls_) {
    ball->bounceIntoWindow((*game.grid_).getWindowHeight(),
                           (*game.grid_).getWindowWidth());

    if (ball->isOut() && game.isLastBall()) {
      game.player_->popLife();
      game.player_->reset();
      ball->reset();
    }

    for (auto brick : game.grid_->getBricks()) {
      manageCollisionBrickBall(brick, ball, game);
    }

    Direction normal = checkCollision(*ball, *game.player_);
    if (normal.isValid()) {
      ball->bounceOverPaddle(*game.player_);
    }
  }

  for (auto bonus : game.getBonusManager()->getBonuses()) {
    if (checkCollision(*bonus, *game.player_).isValid()) {
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

Direction CollisionEngine::checkCollision(Ball &ball, Rectangle &rectangle) {
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

  if (distance >= ball.getRadius()) {
    return Direction(false);
  }
  // else
  if (test_x == rectangle_position.x_) {
    return Direction(-1, 0);
  } else if (test_x == rectangle_position.x_ + rectangle.getWidth()) {
    return Direction(1, 0);
  } else if (test_y == rectangle_position.y_) {
    return Direction(0, -1);
  } else if (test_y == rectangle_position.y_ + rectangle.getHeight()) {
    return Direction(0, 1);
  } else {
    //printf("comportement bizarre : collisionCircleRect\n");
    return Direction(false);
  }
}

Direction CollisionEngine::checkCollision(Ball &ball, Triangle &triangle) {
  std::vector<Line> edges = triangle.getEdges();
  Direction normal;

  for (auto &edge : edges) {
    normal = checkCollision(ball, edge);
    if (normal.isValid()) {
      return normal;
    }
  }
  // we don't check if the circle is totally inside of the triangle : whatever
  return Direction(false);
}

Direction CollisionEngine::checkCollision(Rectangle &rectangle1,
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
  if (overlapX && overlapY) {
    return Direction();
  }
  return Direction(false);
}

Direction CollisionEngine::checkCollision(Ball &ball, Vector2D &point) {
  Vector2D distance = Vector2D(ball.getPosition().x_ - point.x_,
                               ball.getPosition().y_ - point.y_);
  if (distance.getSquaredNorm() < pow(ball.getRadius(), 2)) {
    return Direction(true);
  }
  return Direction(false);
}

Direction CollisionEngine::checkCollision(Ball &ball, Line &line) {
  Vector2D AB = line.getDirection();
  Vector2D AC = Vector2D(ball.getPosition().x_ - line.getStart().x_,
                         ball.getPosition().y_ - line.getStart().y_);
  Vector2D BC = Vector2D(ball.getPosition().x_ - line.getEnd().x_,
                         ball.getPosition().y_ - line.getEnd().y_);

  double distance = abs(AB.vectorialProduct(AC)) / AB.getNorm();
  if (distance > ball.getRadius()) {
    return Direction(false);
  }
  // ball intersects the line line, what about the segment ?

  Vector2D start = line.getStart();
  Vector2D end = line.getEnd();
  if (!((AB.dotProduct(AC) > 0 && AB.dotProduct(BC) < 0) ||
        checkCollision(ball, start).isValid() ||
        checkCollision(ball, end).isValid())) {
    // neither orthogonal projection of circle's radius is between A and B
    // nor A is in the circle
    // nor B is in the circle
    return Direction(false);
  }

  // we can compute the normal
  double product = AB.dotProduct(AC); // we compute only once this product
  return Direction(-AB.y_ * product, AB.x_ * product);
}