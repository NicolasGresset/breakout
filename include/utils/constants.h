#ifndef CONSTANTS_H
#define CONSTANTS_H
#include <SDL_stdinc.h>

constexpr int WINDOW_HEIGHT = 800;
constexpr int WINDOW_WIDTH = 1200;

constexpr int DOCK_HEIGHT = 50;
constexpr int DOCK_WIDTH = 150;

constexpr int PADDING = 20;

constexpr double DOCK_SPEED_X = 2;

constexpr double INITIAL_BALL_POSITION_X = (double)WINDOW_WIDTH / 2;
constexpr double INITIAL_BALL_POSITION_Y = 2 * (double)WINDOW_HEIGHT / 3;

constexpr double BALL_SPEED_NORM = 1;

constexpr double BALL_RADIUS = 20;

constexpr double SQUARE_ROOT_2 = 1.41321356;

constexpr double PI = 3.14159265;

constexpr int DEFAULT_BRICK_LIFE = 1;

constexpr Uint64 FRAME_DURATION = 10; 

#endif
