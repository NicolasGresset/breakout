#ifndef ASSETS_H
#define ASSETS_H

#include "color.h"
#include <SDL2/SDL_render.h>
#include <map>
#include <memory>

class Assets {
private:
  std::map<Color, std::shared_ptr<SDL_Texture>> rectangles_textures_;
  std::map<Color, std::shared_ptr<SDL_Texture>> balls_textures_;

public:
  void loadTextures(SDL_Renderer &renderer);
  inline std::shared_ptr<SDL_Texture> getRectangleTexture(Color color) {
    return rectangles_textures_[color];
  }
  inline std::shared_ptr<SDL_Texture> getBallTexture(Color color) {
    return balls_textures_[color];
  }

private:
  SDL_Texture *loadTexture(const char *path, SDL_Renderer &renderer);
};

#endif