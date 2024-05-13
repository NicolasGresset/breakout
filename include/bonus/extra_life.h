#ifndef EXTRA_LIFE_H
#define EXTRA_LIFE_H

#include "bonus/bonus.h"
#include "game.h"

class ExtraLife : public Bonus {
  inline void action(Game &game) override { game.getPlayer()->addLives(1); }

public:
  ExtraLife();
  ExtraLife(texture_ptr texture, Brick &brick, int width, int height,
            Vector2D speed);
};

#endif