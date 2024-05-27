#ifndef MULTI_BALL_H
#define MULTI_BALL_H

#include "bonus/bonus.h"
#include "collison_engine.h"
#include "object/object.h"
#include "utils/randomiser.h"

class MultiBall : public Bonus {
public:
  MultiBall();
  MultiBall(texture_ptr texture, Brick &brick, int width, int height,
            Vector2D speed);

private:
  void action(LevelState &game) override;
  Randomiser<double> randomiser_;
};

#endif