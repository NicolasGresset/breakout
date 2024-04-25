#ifndef GRID_H
#define GRID_H
#include "gui/assets.h"
#include "object/brick.h"
#include "object/rectangle_brick.h"
#include "utils/constants.h"
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <memory>
#include <vector>

/*
A grid can either be composed of rectangles or hexagons, thus a template class
is required
*/

// template <typename T>
//  on va essayer de faire une grille de rectangles pour l'instant
class Grid {
private:
  std::vector<std::shared_ptr<RectangleBrick>> bricks_;
  const int height_;
  const int width_;
  double window_height_;
  double window_width_;

  std::shared_ptr<Assets> assets_;

public:
  void init();

private:
  RectangleBrick initializeElement(const int i, const int j);

public:
  Grid();
  /*
  // Width corresponds to the number of bricks on the width of the screen
  // Height corresponds to the number of bricks on the height of the screen

  // for instance, for a 3*4 grid, call Grid(3, 4)
  // the convention is similar to matrixes
  */
  Grid(const int height, const int width, const double window_height,
       const double window_width, std::shared_ptr<Assets> assets);

  Grid(std::shared_ptr<Assets> assets);

  void draw(SDL_Renderer& renderer) const;

  inline std::vector<std::shared_ptr<RectangleBrick>> &getBricks() {
    return bricks_;
  }

  inline double getWindowHeight() { return window_height_; }
  inline double getWindowWidth() { return window_width_; }
};

#endif