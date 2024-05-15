#ifndef SPEED_BALL_H
#define SPEED_BALL_H

#include "bonus/bonus.h"
#include "game.h"
#include "utils/constants.h"
#include "utils/utils.h"
#include "utils/vector2D.h"

class SpeedBall : public Bonus {
  void action(Game &game) override {
    balls_ptr balls = game.getBall();
    for (auto ball : *balls) {
      Vector2D new_speed(ball->getSpeed());
      new_speed.x_ *= coefficient_;
      new_speed.y_ *= coefficient_;

      double delta = abs(ball->getSpeed().getAngle() - new_speed.getAngle());
      ASSERT_FN(delta < EPSILON, [&]() {
        std::cerr << "Changing the speed should not change the direction of "
                     "the ball, but there is : "
                  << delta << " radians difference\n";
      });
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
