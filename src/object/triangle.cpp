#include "object/triangle.h"
#include "object/object.h"
#include "utils/constants.h"
#include "utils/utils.h"
#include <SDL_rect.h>

Triangle::Triangle() : Object() {}
Triangle::Triangle(double orientation, double length)
    : Object(), orientation_(orientation), length_(length) {}

Triangle::Triangle(Vector2D position, texture_ptr texture, double orientation,
                   double length)
    : Object(position, texture), orientation_(orientation), length_(length) {}

void Triangle::draw(SDL_Renderer &renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();
  SDL_Rect destinationRect = {(int)upper_left_coords.x_,
                              (int)upper_left_coords.y_, (int)length_,
                              (int)(length_ * SQUARE_ROOT_3 / 2)};

  SDL_Point center = {static_cast<int>(position_.x_),
                      static_cast<int>(position_.y_)};
  CHECK_SDL_RETURN_CODE(SDL_RenderCopyEx(&renderer, texture_->at(0), NULL,
                                         &destinationRect, orientation_,
                                         &center, SDL_FLIP_NONE) < 0);
}