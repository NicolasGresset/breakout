#include "../include/ball.h"
#include "constants.h"
#include "vector2D.h"
#include <SDL_render.h>

#include <algorithm>
#include <iostream>

Ball::Ball(SDL_Texture *texture)
    : Object(Vector2D(INITIAL_BALL_POSITION_X, INITIAL_BALL_POSITION_Y),
             texture),
      radius_(BALL_RADIUS), speed_(0, BALL_SPEED_NORM),
      rounding_square_side_length(radius_ * SQUARE_ROOT_2) {}

void Ball::draw(SDL_Renderer *renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();

  SDL_Rect destinationRect = {
      (int)upper_left_coords.x_, (int)upper_left_coords.y_,
      (int)rounding_square_side_length, (int)rounding_square_side_length};

  if (SDL_RenderCopy(renderer, texture_, NULL, &destinationRect) < 0) {
    std::cerr << "unable to render rectangle brick : "
              << std::string{SDL_GetError()} << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Ball::move() {
  position_.x_ += speed_.x_;
  position_.y_ += speed_.y_;
}

int Ball::bounceIntoWindow(double height, double width) {
  if (this->position_.y_ + this->radius_ > height) {
    reset();
    return 0;
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

  return 1;
}

void Ball::reset(){
  speed_.x_ = 0;
  speed_.y_ = BALL_SPEED_NORM;
  position_.x_ = INITIAL_BALL_POSITION_X;
  position_.y_ = INITIAL_BALL_POSITION_Y;
}