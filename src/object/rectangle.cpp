#include "object/rectangle.h"
#include "utils/utils.h"
#include <SDL_render.h>
#include <cstddef>
#include <iostream>

Rectangle::Rectangle(Vector2D position, SDL_Texture *texture, double width,
                     double height)
    : Object(position, texture), width_(width), height_(height){};

Rectangle::Rectangle() : Object(), width_(0), height_(0){};

// Rectangle::Rectangle(double width, double height) : Object(), width_(width),
// height_(height){}

void Rectangle::draw(SDL_Renderer &renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();
  SDL_Rect destinationRect = {(int)upper_left_coords.x_,
                              (int)upper_left_coords.y_, (int)width_,
                              (int)height_};

  int code = SDL_RenderCopy(&renderer, texture_, NULL, &destinationRect);
  CHECK_SDL_RETURN_CODE(code < 0);
}
