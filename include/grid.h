#ifndef GRID_H
#define GRID_H
#include "gui/assets.h"
#include "object/brick.h"
#include "object/rectangle_brick.h"
#include "object/triangle_brick.h"
#include "utils/constants.h"
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>


class Grid {
private:
  std::vector<std::shared_ptr<Brick>> bricks_;
  const int height_;
  const int width_;
  double window_height_;
  double window_width_;

  std::shared_ptr<Assets> assets_;

  std::string grid_path_;

public:
  void init();

private:
  RectangleBrick initializeElement(const int i, const int j);
  std::shared_ptr<Brick> last_destroyed_brick_;
  void openGridFromFile();
  void initTriangleGrid();
  void initRectangleGrid();

public:
  Grid();
  /*
  // Width corresponds to the number of bricks on the width of the screen
  // Height corresponds to the number of bricks on the height of the screen

  // for instance, for a 3*4 grid, call Grid(3, 4)
  // the convention is similar to matrixes
  */
  Grid(const int width, const int height, const double window_width,
       const double window_height, std::shared_ptr<Assets> assets,
       std::string grid_path_ = "");

  Grid(std::shared_ptr<Assets> assets);

  void draw(SDL_Renderer &renderer) const;

  inline std::vector<std::shared_ptr<Brick>> &getBricks() {
    return bricks_;
  }

  inline double getWindowHeight() { return window_height_; }
  inline double getWindowWidth() { return window_width_; }

  inline void setLastDestroyedBrick(std::shared_ptr<Brick> brick) {
    last_destroyed_brick_ = brick;
  }

  inline Brick &getLastDestroyedBrick() { return *last_destroyed_brick_; }
};

#endif
