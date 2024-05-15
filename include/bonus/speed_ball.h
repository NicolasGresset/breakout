#ifndef SPEED_BALL_H
#define SPEED_BALL_H

#include "bonus/bonus.h"
#include "game.h"
#include "utils/vector2D.h"

class SpeedBall : public Bonus {
  void action(Game &game) override {
    printf("got extra speed\n");
    balls_ptr balls = game.getBall();
    for (auto ball : *balls) {
      Vector2D new_speed(ball->getSpeed());
      double norm = ball->getSpeed().getNorm();
      double angle = tan(ball->getSpeed().y_ / ball->getSpeed().x_);
      new_speed.x_ += (coefficient_ - 1) * norm * cos(angle);
      new_speed.y_ += (coefficient_ - 1) * norm * sin(angle);
      ball->setSpeed(new_speed);
    }
  }

private:
  const double coefficient_ = 1.5;

public:
  SpeedBall();
  SpeedBall(texture_ptr texture, Brick &brick, int width, int height,
            Vector2D speed);
};

#endif
