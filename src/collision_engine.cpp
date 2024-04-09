#include "collison_engine.h"
#include "dock.h"
#include "rectangle_brick.h"
#include <vector>

CollisionEngine::CollisionEngine(std::vector<Ball> &balls, Grid &grid,
                                 Dock &player)
    : balls_(balls), grid_(grid), player_(player) {};

void CollisionEngine::resolveCollisions(){

}

bool CollisionEngine::ballIntersectRectangle(Ball &ball, RectangleBrick &brick) const{
    // We first check if the two Axis Aligned Bounding Box collide

}