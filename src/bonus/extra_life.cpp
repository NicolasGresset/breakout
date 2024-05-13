#include "bonus/extra_life.h"
#include "object/object.h"

ExtraLife::ExtraLife() : Bonus() {}

ExtraLife::ExtraLife(texture_ptr texture, Brick &brick, int width, int height,
                     Vector2D speed)
    : Object(brick.getPosition(), texture),
      Bonus(texture, brick, width, height, speed) {}