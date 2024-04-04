#ifndef SDL2WINDOW_H
#define SDL2WINDOW_H

#include "color.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <map>
#include <string>

class SDL2Window {
private:
  const int screen_width_;
  const int screen_height_;
  SDL_Window *window_;

  // We use a renderer instead of a surface because it is GPU-accelerated
  SDL_Renderer *renderer_;

  std::map<Color, SDL_Texture *> rectangles_textures_;
  std::map<Color, SDL_Texture *> balls_textures_;

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

  void loadTextures(void);

  void foo(void);

private:
  SDL_Texture *loadTexture(const char *path);
};

#endif