#include "grid.h"
#include "utils/constants.h"
#include <SDL2/SDL_render.h>
#include <iostream>

Grid::Grid(const int height, const int width, double window_height,
           double window_width, Assets *assets)
    : height_(height), width_(width), window_height_(window_height),
      window_width_(window_width), assets_(assets){};

Grid::Grid(Assets *assets)
    : height_(10), width_(8), window_height_(WINDOW_HEIGHT), window_width_(WINDOW_WIDTH),
      assets_(assets) {}

void Grid::init() {
  double element_height = window_height_ / (2 * height_);
  double element_width = window_width_ / width_;
  for (int i{0}; i < height_; i++) {
    for (int j{0}; j < width_; j++) {
      bricks_.push_back(
          RectangleBrick(Vector2D(j * element_width + element_width / 2,
                                  i * element_height + element_height / 2),
                         assets_->getRectangleTexture(Color::red), 1,
                         element_width, element_height));
    }
  }
}

void Grid::draw(SDL_Renderer *renderer) const {
  for (auto brick : bricks_) {
    brick.draw(renderer);
  }
}
