#ifndef SDL2WINDOW_H
#define SDL2WINDOW_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>

class SDL2Window {
private:
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;
  SDL_Renderer *renderer_;

public:
  SDL2Window();
  SDL2Window(int screen_width, int screen_height);

  void init();
  void update();
  ~SDL2Window();

  inline void temporisation(Uint32 ms) const { SDL_Delay(ms); }

public:
  void drawCirle(double centerX, double centerY, double radius);
  void fillCircle(double centerX, double centerY, double radius);
};

#endif