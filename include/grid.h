#ifndef GRID_H
#define GRID_H
#include <vector>
#include "brick.h"

/*
A grid can either be composed of rectangles or hexagons, thus a template class is required
*/

template<typename T>
class Grid{
    private:
    std::vector<T> bricks;


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