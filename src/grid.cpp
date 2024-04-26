#include "grid.h"
#include "utils/constants.h"
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <iostream>

Grid::Grid()
    : bricks_(), height_(), width_(), window_height_(), window_width_(),
      assets_(){};

Grid::Grid(const int height, const int width, double window_height,
           double window_width, std::shared_ptr<Assets> assets)
    : height_(height), width_(width), window_height_(window_height),
      window_width_(window_width), assets_(assets) {
  init();
};

Grid::Grid(std::shared_ptr<Assets> assets)
    : bricks_(), height_(), width_(), window_height_(), window_width_(),
      assets_(assets) {}

void Grid::init() {
  double element_height = window_height_ / (2 * height_);
  double element_width = window_width_ / width_;
  for (int i{0}; i < height_; i++) {
    for (int j{0}; j < width_; j++) {
      bricks_.push_back(std::make_shared<RectangleBrick>(
          Vector2D(j * element_width + element_width / 2,
                   i * element_height + element_height / 2),
          assets_->getRectangleTexture(Color::red), 1, element_width,
          element_height));
    }
  }
}

void Grid::draw(SDL_Renderer &renderer) const {
  for (auto brick : bricks_) {
    brick->draw(renderer);
  }
}
