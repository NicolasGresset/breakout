#include "object/ball.h"
#include "object/dock.h"
#include "utils/constants.h"
#include "utils/utils.h"
#include "utils/vector2D.h"
#include <SDL_render.h>

#include <SDL_timer.h>
#include <cstdio>

#include "utils/direction.h"

Ball::Ball()
    : Object(), MovableObject(), radius_(0), rounding_square_side_length(0){};

Ball::Ball(Vector2D position, texture_ptr texture, Vector2D speed,
           double radius)
    : Object(position, texture), MovableObject(speed), radius_(radius),
      rounding_square_side_length(radius * SQUARE_ROOT_2) {}

// Ball::Ball(SDL_Texture *texture)
//     : MovableObject(Vector2D(INITIAL_BALL_POSITION_X,
//     INITIAL_BALL_POSITION_Y),
//                     texture, Vector2D(0, BALL_SPEED_NORM)),
//       radius_(BALL_RADIUS),
//       rounding_square_side_length(radius_ * SQUARE_ROOT_2) {}

void Ball::draw(SDL_Renderer &renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();

  SDL_Rect destinationRect = {
      (int)upper_left_coords.x_, (int)upper_left_coords.y_,
      (int)rounding_square_side_length, (int)rounding_square_side_length};

  int code = SDL_RenderCopy(&renderer, texture_->at(0), NULL, &destinationRect);
  CHECK_SDL_RETURN_CODE(code < 0);
}

void Ball::bounceIntoWindow(double height, double width) {
  if (this->position_.y_ + this->radius_ > height) {
    is_out_ = true;
  }

  if (this->position_.x_ + this->radius_ > width) {
    speed_.x_ = -speed_.x_;
  }

  if (this->position_.x_ - this->radius_ < 0) {
    speed_.x_ = -speed_.x_;
  }

  if (this->position_.y_ - this->radius_ < 0) {
    speed_.y_ = -speed_.y_;
  }
}

void Ball::reset() {
  speed_.x_ = 0;
  speed_.y_ = BALL_SPEED_NORM;
  position_.x_ = INITIAL_BALL_POSITION_X;
  position_.y_ = INITIAL_BALL_POSITION_Y;
  is_out_ = false;
}

void Ball::bounceOverPaddle(const Dock &paddle) {
  /* the ball is assumed to bounce over the paddle with a reflection angle
   * proportional to the distance between the point of impact and the paddle
   * center */

  /* this computation maps the bouncing angle between [3 pi / 2 + delta, 5 pi /
   * 2 - delta] */

  // bouncing over the side
  if (position_.y_ + radius_ >
      paddle.getPosition().y_ + paddle.getHeight() / 2) {
    printf("we bounce over the side\n");
    speed_.x_ = -speed_.x_;
    return;
  }

  double path_angle = ((-PI + 2 * delta_) / paddle.getWidth()) *
                          (-position_.x_ + (paddle.getPosition().x_)) -
                      PI / 2;

  double norm = speed_.getNorm();
  speed_.x_ = norm * cos(path_angle);
  speed_.y_ = norm * sin(path_angle);
}

void Ball::bounceOverLine(const Direction &normal) {
  double dot_product = normal.getVector().dotProduct(speed_);
  speed_.x_ -= 2 * dot_product * normal.getVector().x_;
  speed_.y_ -= 2 * dot_product * normal.getVector().y_;
}
