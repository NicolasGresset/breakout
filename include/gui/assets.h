#ifndef ASSETS_H
#define ASSETS_H

#include "color.h"
#include <SDL2/SDL_render.h>
#include <map>

class Assets {
private:
  std::map<Color, SDL_Texture *> rectangles_textures_;
  std::map<Color, SDL_Texture *> balls_textures_;
  SDL_Renderer *renderer_;

public:
  void loadTextures(SDL_Renderer *renderer);
  inline SDL_Texture *getRectangleTexture(Color color) {
    return rectangles_textures_[color];
  }
  inline SDL_Texture *getBallTexture(Color color) {
    return balls_textures_[color];
  }

private:
  SDL_Texture *loadTexture(const char *path);
};

#endif