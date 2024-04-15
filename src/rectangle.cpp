#include "../include/rectangle.h"
#include <SDL_render.h>
#include <cstddef>
#include <iostream>
#include "utils.h"

Rectangle::Rectangle(Vector2D position, SDL_Texture *texture, double width,
                     double height)
    : Object(position, texture), width_(width), height_(height){};

Rectangle::Rectangle() : Object(Vector2D{0, 0}, nullptr){};

void Rectangle::draw(SDL_Renderer *renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();
  SDL_Rect destinationRect = {(int)upper_left_coords.getX(),
                              (int)upper_left_coords.getY(), (int)width_,
                              (int)height_};

  int code = SDL_RenderCopy(renderer, texture_, NULL, &destinationRect);
  checkSDLReturnCode(code < 0);
}