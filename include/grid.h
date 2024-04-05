#ifndef GRID_H
#define GRID_H
#include "brick.h"
#include "rectangle_brick.h"
#include <vector>

/*
A grid can either be composed of rectangles or hexagons, thus a template class
is required
*/

//template <typename T> 
// on va essayer de faire une grille de rectangles pour l'instant
class Grid {
private:
  std::vector<RectangleBrick> bricks_;
  const int height_;
  const int width_;

  void initializeGrid(void);

public:
  Grid();

  /*
  // Width corresponds to the number of bricks on the width of the screen
  // Height corresponds to the number of bricks on the height of the screen

  // for instance, for a 3*4 grid, call Grid(3, 4)
  // the convention is similar to matrixes
  */
  Grid(const int height, const int width);
};

#endif