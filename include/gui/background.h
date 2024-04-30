#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SDL_render.h>
#include <memory>
#include <vector>

class Background {
private:
  std::shared_ptr<std::vector<SDL_Texture *>> background_texture_;
  const int screen_width_;
  const int screen_height_;

  // the frame to be displayed at this call of draw : valid index of
  // background_texture
  int current_frame_ = 0;

  // the number of frames we display the same background
  const int same_frame_ = 20;

  // the number of frames we-ve already displayed this background
  int nb_frames_ = 0;

  // are we incrementing frames or not ?
  bool raising_values = true;

public:
  Background();
  Background(std::shared_ptr<std::vector<SDL_Texture *>> background_texture,
             int screen_width, int screen_height);

  void draw(SDL_Renderer &renderer) ;

  private:
    void updateFrames();
};

#endif