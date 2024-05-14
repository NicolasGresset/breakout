#include "object/rectangle.h"
#include "utils/utils.h"

Rectangle::Rectangle(Vector2D position, texture_ptr texture, double width,
                     double height)
    : Object(position, texture), width_(width), height_(height){};

Rectangle::Rectangle() : Object(), width_(0), height_(0){};

Rectangle::Rectangle(double width, double height)
    : Object(), width_(width), height_(height) {}

// Rectangle::Rectangle(double width, double height) : Object(), width_(width),
// height_(height){}

void Rectangle::draw(SDL_Renderer &renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();
  SDL_Rect destinationRect = {(int)upper_left_coords.x_,
                              (int)upper_left_coords.y_, (int)width_,
                              (int)height_};

  int code = SDL_RenderCopy(&renderer, texture_->at(0), NULL, &destinationRect);
  CHECK_SDL_RETURN_CODE(code < 0);
}
