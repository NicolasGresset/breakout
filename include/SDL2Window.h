#ifndef SDL2WINDOW_H
#define SDL2WINDOW_H

#include <SDL2/SDL.h>

class SDL2Window {
private:
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;
  SDL_Surface *screen_surface_;

public:
  SDL2Window();
  SDL2Window(int screen_width, int screen_height);

  void init();
  void update();
  ~SDL2Window();
};

#endif