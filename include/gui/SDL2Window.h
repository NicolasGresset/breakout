#ifndef SDL2WINDOW_H
#define SDL2WINDOW_H

#include "assets.h"
#include "background.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL_video.h>
#include <map>
#include <memory>
#include <string>

class SDL2Window {
protected:
  const int screen_width_;
  const int screen_height_;
  std::shared_ptr<SDL_Window> window_;

  // We use a renderer instead of a surface because it is GPU-accelerated
  std::shared_ptr<SDL_Renderer> renderer_;

public:
  SDL2Window();
  SDL2Window(int screen_width, int screen_height);
  ~SDL2Window();

private:
  void initSDLObjects();

public:
  inline void update() { SDL_RenderPresent(renderer_.get()); }
  inline void temporisation(Uint32 ms) const { SDL_Delay(ms); }
  inline SDL_Renderer &getRenderer(void) { return *renderer_; }
  inline void clearWindow(void) { SDL_RenderClear(renderer_.get()); }
};

#endif