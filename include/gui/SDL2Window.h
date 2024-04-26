#ifndef SDL2WINDOW_H
#define SDL2WINDOW_H

#include "assets.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL_video.h>
#include <map>
#include <memory>
#include <string>

class SDL2Window {
private:
  const int screen_width_;
  const int screen_height_;
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> window_;

  // We use a renderer instead of a surface because it is GPU-accelerated
  std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)> renderer_;

public:
  SDL2Window();
  SDL2Window(int screen_width, int screen_height);

private:
  void init();
  void initSDLObjects();

public:
  void update();
  ~SDL2Window();

  inline void temporisation(Uint32 ms) const { SDL_Delay(ms); }
  inline SDL_Renderer &getRenderer(void) { return *renderer_; }
  inline void clearWindow(void) { SDL_RenderClear(renderer_.get()); }

public:
  void drawCirle(double centerX, double centerY, double radius);
  void fillCircle(double centerX, double centerY, double radius);

  // void foo(void);
};

#endif