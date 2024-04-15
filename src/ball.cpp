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
      (int)upper_left_coords.getX(), (int)upper_left_coords.getY(),
      (int)rounding_square_side_length, (int)rounding_square_side_length};

  if (SDL_RenderCopy(renderer, texture_, NULL, &destinationRect) < 0) {
    std::cerr << "unable to render rectangle brick : "
              << std::string{SDL_GetError()} << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Ball::move() {
  position_.setX(position_.getX() + speed_.getX());
  position_.setY(position_.getY() + speed_.getY());
}

int Ball::bounceIntoWindow(double height, double width) {
  if (this->position_.getY() + this->radius_ > height) {
    reset();
    return 0;
  }

  if (this->position_.getX() + this->radius_ > width) {
    this->speed_.setX((-this->speed_.getX()));
  }

  if (this->position_.getX() - this->radius_ < 0) {
    this->speed_.setX((-this->speed_.getX()));
  }

  if (this->position_.getY() - this->radius_ < 0) {
    this->speed_.setY((-this->speed_.getY()));
  }

  return 1;
}

void Ball::reset(){
  this->speed_.setX(0);
  this->speed_.setY(BALL_SPEED_NORM);
  this->position_.setX(INITIAL_BALL_POSITION_X);
  this->position_.setY(INITIAL_BALL_POSITION_Y);
}