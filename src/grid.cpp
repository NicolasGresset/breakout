#include "../include/grid.h"

Grid::Grid() : height_{4}, width_{8}{}

Grid::Grid(const int height, const int width) : height_(height), width_(width){}


void Grid::initializeGrid(){
    unsigned int n_bricks = height_ * width_;
    for (unsigned int i{0}; i<height_; i++){
        for (unsigned int j{0}; j<width_; j++){
            bricks_.push_back()

        }
    }
}