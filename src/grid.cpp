#include "../include/grid.h"

Grid::Grid(const int height = 4, const int width = 8,
           double window_height = 500, double window_width = 800)
    : height_(height), width_(width), window_height_(window_height),
      window_width_(window_width){};

RectangleBrick Grid::initializeElement(const int i, const int j) {
  return RectangleBrick(Vector2D(i *))
}

void Grid::initializeGrid() {
  double element_height = window_height_ / height_;
  double element_width = window_width_ / width_;
  for (unsigned int i{0}; i < height_; i++) {
    for (unsigned int j{0}; j < width_; j++) {
      bricks_.push_back(
          RectangleBrick(Vector2D(j * element_width + element_width / 2,
                                  i * element_height + element_height / 2),
                         Color::red, 3, element_width, element_height));
    }
  }
}