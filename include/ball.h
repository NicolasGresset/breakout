#ifndef BALL_H
#define BALL_H

#include "constants.h"
#include "dock.h"
#include "object.h"
#include "rectangle.h"
#include "vector2D.h"
#include <SDL_render.h>

/**
Just like dock, a ball is a movable object with such attributes
we should consider multiple heritance
#todo
*/
class Ball : public MovableObject {
private:
  double radius_;
  double rounding_square_side_length;
  double path_angle_;

  double delta_ =
      0.1; // used to calculate direction when bouncing over the paddle

public:
  Ball(SDL_Texture *texture = nullptr);

  void draw(SDL_Renderer *renderer) const override;

private:
  inline Vector2D toUpperLeftCoords() const override {
    return Vector2D(position_.x_ - radius_ / 2, position_.y_ - radius_ / 2);
  }

public:
  /*
  Checks wether the ball is colliding outside of the boundaries of the window
  and updates its speed accordingly
  */
  int bounceIntoWindow(double height, double width);

  void bounceOverRectangle(const Rectangle &rectangle);

  void bounceOverPaddle(const Dock &paddle);

  inline double getRadius() const { return radius_; }


  void reset();
};

#endif