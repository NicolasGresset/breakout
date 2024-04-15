#ifndef BALL_H
#define BALL_H

#include "constants.h"
#include "object.h"
#include "vector2D.h"
#include <SDL_render.h>

/**
Just like dock, a ball is a movable object with such attributes
we should consider multiple heritance
#todo
*/
class Ball : public Object {
  double radius_;
  Vector2D speed_;
  double rounding_square_side_length;
  double path_angle_;

public:
  Ball(SDL_Texture *texture = nullptr);

  void draw(SDL_Renderer *renderer) const override;

private:
  inline Vector2D toUpperLeftCoords() const {
    return Vector2D(position_.getX() - radius_ / 2,
                    position_.getY() - radius_ / 2);
  }

public:
  void move();

  /*
  Checks wether the ball is colliding outside of the boundaries of the window and updates its speed accordingly
  */
  int bounceIntoWindow(double height, double width);

  void reset();
};

#endif