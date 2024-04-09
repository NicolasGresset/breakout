#ifndef GRID_H
#define GRID_H
#include "assets.h"
#include "brick.h"
#include "rectangle_brick.h"
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
  Grid(const int height = 4, const int width = 8, const double window_height = 500,
       const double window_width = 800, Assets *assets= nullptr);

  Grid(Assets * assets);


  void draw (SDL_Renderer *renderer) const;
};

#endif