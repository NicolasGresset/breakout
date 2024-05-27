#ifndef EXTRA_LIFE_H
#define EXTRA_LIFE_H

#include "bonus/bonus.h"
#include "collison_engine.h"
#include "states/level_state.h"

class ExtraLife : public Bonus {
  inline void action(LevelState &game) override { game.addLives(1); }

public:
  ExtraLife();
  ExtraLife(texture_ptr texture, Brick &brick, int width, int height,
            Vector2D speed);
};

#endif