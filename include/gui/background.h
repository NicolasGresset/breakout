#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_render.h>
#include <SDL_stdinc.h>
#include <memory>
#include <vector>

class ElementBackground {
private:
  std::shared_ptr<std::vector<SDL_Texture *>> background_texture_;
  SDL_Texture *current_texture_;
  const int screen_width_;
  const int screen_height_;

  // center of the image
  Vector2D position_;

  // the index of the frame to be displayed at this call of draw : valid index
  // of background_texture
  int current_frame_ = 0;

  // the number of frames we display the same background
  const int same_frame_ = 20;

  // the number of frames we-ve already displayed this background
  int nb_frames_ = 0;

  // are we incrementing frames or not ?
  bool raising_values = true;

public:
  ElementBackground();
  ElementBackground(
      std::shared_ptr<std::vector<SDL_Texture *>> background_texture,
      int screen_width, int screen_height);

  void draw(SDL_Renderer &renderer);

  inline void update(Uint64 delta) {
    total_time_ += delta;
    current_texture_ = background_texture_->at(current_frame_);
  }

private:
  Uint64 total_time_;
  SDL_Point center_;
  SDL_Rect rect_;

  Uint64 reset_threshold_ = 1000;
  void updateFrames();
  // rotate once every reset_threshold milliseconds
  inline double getAngle() {
    return ((static_cast<double>(total_time_ % reset_threshold_) /
             reset_threshold_) *
            360);
  }

public:
  // amount in percentage to speed up background rotation;s
  void speedUp(double amount);
};

#endif