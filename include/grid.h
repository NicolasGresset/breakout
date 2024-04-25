#ifndef GRID_H
#define GRID_H
#include "gui/assets.h"
#include "object/brick.h"
#include "utils/constants.h"
#include "object/rectangle_brick.h"
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <vector>

/*
A grid can either be composed of rectangles or hexagons, thus a template class
is required
*/

// template <typename T>
//  on va essayer de faire une grille de rectangles pour l'instant
class Grid {
private:
  std::vector<RectangleBrick> bricks_;
  const int height_;
  const int width_;
  double window_height_;
  double window_width_;

  Assets *assets_;

public:
  void init();

private:
  RectangleBrick initializeElement(const int i, const int j);

public:
  /*
  // Width corresponds to the number of bricks on the width of the screen
  // Height corresponds to the number of bricks on the height of the screen

  // for instance, for a 3*4 grid, call Grid(3, 4)
  // the convention is similar to matrixes
  */
  Grid(const int height = 4, const int width = 8,
       const double window_height = WINDOW_HEIGHT,
       const double window_width = WINDOW_WIDTH, Assets *assets = nullptr);

  Grid(Assets *assets);

  void draw(SDL_Renderer *renderer) const;

  inline std::vector<RectangleBrick> &getBricks() { return bricks_; }

  inline double getWindowHeight() { return window_height_; }
  inline double getWindowWidth() { return window_width_; }
};

#endif