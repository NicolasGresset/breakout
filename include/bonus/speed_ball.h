#ifndef SPEED_BALL_H
#define SPEED_BALL_H

#include "bonus/bonus.h"
#include "game.h"
#include <iostream>
class SpeedBall : public Bonus {
    void action(Game &game) override {
        balls_ptr balls = game.getBall();
        for (auto ball : *balls)
        {
            Vector2D speed = ball->getSpeed();
            speed.x_ += 0.5;
            speed.y_ += 0.5;
            ball->setSpeed(speed);
        }
    }
public:
    SpeedBall();
    SpeedBall(texture_ptr texture, Brick &brick, int width, int height,
              Vector2D speed);
};

#endif
