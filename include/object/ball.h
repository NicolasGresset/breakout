#ifndef BALL_H
#define BALL_H

#include "object.h"
#include "utils/vector2D.h"
#include <SDL_render.h>


class Dock;
class Direction;
class Rectangle;

/**
 * @brief Represents the ball, a movable object with some bouncing characteristics (e.g over the paddle)
 * 
 */
class Ball : public MovableObject {
private:
  double radius_;
  double rounding_square_side_length;

  double delta_ =
      0.3; // used to calculate direction when bouncing over the paddle

  bool is_out_ = false;

public:
  Ball();
  Ball(Vector2D position, texture_ptr texture, Vector2D speed, double radius);
  // Ball(SDL_Texture *texture);

  void draw(SDL_Renderer &renderer) const override;

private:
  inline Vector2D toUpperLeftCoords() const override {
    return Vector2D(position_.x_ - radius_ / 2, position_.y_ - radius_ / 2);
  }

public:
  /*
  Checks wether the ball is colliding outside of the boundaries of the window
  and updates its speed accordingly
  */
  void bounceIntoWindow(double height, double width);

  void bounceOverPaddle(const Dock &paddle);

  void bounceOverLine(const Direction &line);

  inline double getRadius() const { return radius_; }

  void reset();

  inline bool isOut() const { return is_out_; }
};

#endif