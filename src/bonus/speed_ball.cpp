#include "bonus/speed_ball.h"
#include "object/object.h"

SpeedBall::SpeedBall() : Bonus() {}

SpeedBall::SpeedBall(texture_ptr texture, Brick &brick, int width, int height,
                     Vector2D speed)
    : Object(brick.getPosition(), texture),
      Bonus(texture, brick, width, height, speed) {}
