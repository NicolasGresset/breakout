#include "grid.h"
#include "utils/constants.h"
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <iostream>
#include <fstream>

Grid::Grid()
    : bricks_(), height_(), width_(), window_height_(), window_width_(),
      assets_(){};

Grid::Grid(const int width, const int height, double window_width,
           double window_height, std::shared_ptr<Assets> assets, std::string grid_path)
    : height_(height), width_(width), window_height_(window_height),
      window_width_(window_width), assets_(assets), grid_path_(grid_path) {
  init();
};

Grid::Grid(std::shared_ptr<Assets> assets)
    : bricks_(), height_(), width_(), window_height_(), window_width_(),
      assets_(assets) {}

void Grid::init() {

   if (grid_path_ != "")
   {
       // Init with a file
       std::ifstream file(grid_path_);

       if (!file.is_open()) {
           // Handle file open error
           std::cout << "Erreur dans la lecture du niveau" << std::endl;
           exit(1);
       }

       int width, height;
       file >> width >> height;

       double element_height = window_height_ / (4 * height);
       double element_width = window_width_ / width;

       int brickType;
       Color color;
       for (int i{0}; i < height; ++i) {
           for (int j{0}; j < width; ++j) {

               file >> brickType;
               switch (brickType){
               case 1:
                   color = Color::red;
                   break;
               case 2:
                   color = Color::blue;
                   break;
               case 3:
                   color = Color::green;
                   break;
               case 5:
                   color = Color::purple;
                   break;
               default:
                   color = Color::yellow;
                   break;
               }
               if (color == Color::yellow)
                   continue;
               bricks_.push_back(std::make_shared<RectangleBrick>(
                       Vector2D(j * element_width + element_width / 2,
                                i * element_height + element_height / 2),
                       assets_->getRectangleTexture(color), 1, element_width,
                       element_height));
           }
       }
   }
   else
   {
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
}

void Grid::draw(SDL_Renderer &renderer) const {
  for (auto brick : bricks_) {
    brick->draw(renderer);
  }
}
