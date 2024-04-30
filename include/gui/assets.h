#ifndef ASSETS_H
#define ASSETS_H

#include "color.h"
#include <SDL2/SDL_render.h>
#include <map>
#include <memory>
#include <vector>

class Assets {
private:
  // can't use smart pointers because SDL_Texture is an incomplete type
  std::map<Color, SDL_Texture *> rectangles_textures_;
  std::map<Color, SDL_Texture *> balls_textures_;
  std::vector<SDL_Texture *> background_texture_;

public:
  Assets() {}
  inline Assets(SDL_Renderer &renderer) { loadTextures(renderer); }
  inline SDL_Texture *getRectangleTexture(Color color) {
    return rectangles_textures_[color];
  }
  inline SDL_Texture *getBallTexture(Color color) {
    return balls_textures_[color];
  }

  inline std::shared_ptr<std::vector<SDL_Texture *>> getBackgroundTexture() {
    return std::make_shared<std::vector<SDL_Texture *>>(background_texture_);
  }

private:
  void loadTextures(SDL_Renderer &renderer);
  SDL_Texture *loadTexture(const char *path, SDL_Renderer &renderer);
};

#endif