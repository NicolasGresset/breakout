#include "bonus/multi_ball.h"
#include "collison_engine.h"
#include "object/object.h"
#include "states/level_state.h"
#include "utils/constants.h"

MultiBall::MultiBall() : Bonus() {}

MultiBall::MultiBall(texture_ptr texture, Brick &brick, int width, int height,
                     Vector2D speed)
    : Object(brick.getPosition(), texture),
      Bonus(texture, brick, width, height, speed), randomiser_(0, 2 * PI) {}

void MultiBall::action(LevelState &game) {
  // we are going to add 3 balls in pseudo-random directions
  for (int i(0); i < 3; i++) {
    game.addBall(randomiser_.generate());
  }
}