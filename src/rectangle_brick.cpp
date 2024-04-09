#include "../include/rectangle_brick.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>

RectangleBrick::RectangleBrick(Vector2D position, SDL_Texture *texture,
                               int life, double width, double height)
    : Brick(position, texture, life), width_(width), height_(height){};
RectangleBrick::RectangleBrick() : Brick(Vector2D{0, 0}, nullptr, 3){};

Vector2D RectangleBrick::toUpperLeftCoords() const {
  return Vector2D(position_.getX() - width_ / 2,
                  position_.getY() - height_ / 2);
}

void RectangleBrick::draw(SDL_Renderer *renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();
  SDL_Rect destinationRect = {(int)upper_left_coords.getX(),
                              (int)upper_left_coords.getY(), (int)width_,
                              (int)height_}; // x, y, width, height

  if (SDL_RenderCopy(renderer, texture_, NULL, &destinationRect) < 0) {
    std::cerr << "unable to render rectangle brick : "
              << std::string{SDL_GetError()} << std::endl;
    exit(EXIT_FAILURE);
  }
}