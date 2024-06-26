#ifndef BONUS_H
#define BONUS_H

#include "collison_engine.h"
#include "object/brick.h"
#include "object/object.h"
#include "object/rectangle.h"
#include "utils/vector2D.h"

class LevelState;

/**
 * @brief Virtual class which represents a bonus
 * will be specified into actual bonuses
 *
 */
class Bonus : public Rectangle, public MovableObject {
public:
  static const int implemented_bonus_types = 3;
  Bonus();
  Bonus(texture_ptr texture, Brick &brick, int width, int height,
        Vector2D speed);

  // the effect of the bonus/malus
  virtual void action(LevelState &game) = 0;

  inline void remove() { is_out_ = true; }

  inline bool isOut() { return is_out_; }

  inline void draw(SDL_Renderer &renderer) const override {
    if (!is_out_)
      Rectangle::draw(renderer);
  }

protected:
  bool is_out_ = false;
};

#endif
