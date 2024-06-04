#include "grid.h"
#include "object/rectangle.h"
#include "object/rectangle_brick.h"
#include "object/triangle_brick.h"
#include "utils/constants.h"
#include "utils/utils.h"
#include "utils/vector2D.h"
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>

Grid::Grid()
    : bricks_(), height_(), width_(), window_height_(), window_width_(),
      assets_(){};

Grid::Grid(const int width, const int height, double window_width,
           double window_height, std::shared_ptr<Assets> assets,
           std::string grid_path)
    : height_(height), width_(width), window_height_(window_height),
      window_width_(window_width), assets_(assets), grid_path_(grid_path) {
  init();
};

Grid::Grid(std::shared_ptr<Assets> assets)
    : bricks_(), height_(), width_(), window_height_(), window_width_(),
      assets_(assets) {}

void Grid::openGridFromFile() {
  // Init with a file
  std::ifstream file(grid_path_);


  ASSERT_FN(file.is_open(), [this]() {
    std::cout << "Erreur dans la lecture du niveau : " << grid_path_
              << std::endl;
  });

  int brick_shape;
  file >> brick_shape;

  // width and height of the grid
  int width, height;
  file >> width >> height;

  int brick_type;
  Color color;
  int life{0};
  for (int i{0}; i < height; ++i) {
    for (int j{0}; j < width; ++j) {

      file >> brick_type;
      switch (brick_type) {
      case 1:
        color = Color::red;
        life = 1;
        break;
      case 2:
        color = Color::blue;
        life = 2;
        break;
      case 3:
        color = Color::green;
        life = 3;
        break;
      case 4:
        color = Color::purple;
        life = 4;
        break;
      case 5:
        color = Color::yellow;
        life = 5;
        break;
      case 6:
        color = Color::yellow;
        life = 6;
        break;
      default:
        // Not render a brick
        color = Color::black;
        break;
      }
      if (color == Color::black)
        continue;

      if (brick_shape == 0) {
        double element_height = window_height_ / (4 * height);
        double element_width = window_width_ / width;

        bricks_.push_back(std::make_shared<RectangleBrick>(
            Vector2D(j * element_width + element_width / 2,
                     i * element_height + element_height / 2),
            assets_->getRectangleTexture(color), life, element_width,
            element_height));
      } else {
        double side_length = window_width_ / (2 * width);
        double row_height = side_length * sqrt(3) / 2;

        double x = window_width_ / 4 + (side_length / 2) * j;
        double y = row_height * i + window_height_ / 8;
        bricks_.push_back((std::make_shared<TriangleBrick>(
            Vector2D(x, y), assets_->getTriangleTextures(), 1,
            j % 2 == 0 ? 0 : PI, side_length)));
      }
    }
  }
}

void Grid::initTriangleGrid() {
  double side_length = window_width_ / (width_);
  double row_height = side_length * sqrt(3) / 2;

  double x{0}, y{0};
  for (int row_index = 0; row_index < height_; row_index++) {
    for (int col_index = 0; col_index < width_; col_index++) {
      x = window_width_ / 4 + (side_length / 2) * col_index;
      y = row_height * row_index + window_height_ / 8;
      bricks_.push_back((std::make_shared<TriangleBrick>(
          Vector2D(x, y), assets_->getTriangleTextures(), 1,
          col_index % 2 == 0 ? 0 : PI, side_length)));
    }
  }
}

void Grid::initRectangleGrid() {
  double element_height = window_height_ / (4 * height_);
  double element_width = window_width_ / width_;

  // In another function create grid ?
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

void Grid::init() {

  if (grid_path_ != "") {
    openGridFromFile();
  } else {
    initRectangleGrid();
    // initTriangleGrid();
  }
}

void Grid::draw(SDL_Renderer &renderer) const {
  for (auto brick : bricks_) {
    brick->draw(renderer);
  }
}
