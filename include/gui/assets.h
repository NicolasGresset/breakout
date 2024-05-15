#ifndef ASSETS_H
#define ASSETS_H

#include "color.h"
#include "object/object.h"
#include <SDL2/SDL_render.h>
#include <map>
#include <memory>
#include <vector>

class Assets {
private:
  // can't use smart pointers because SDL_Texture is an incomplete type
  std::map<Color, std::vector<SDL_Texture *>> rectangles_textures_;
  std::map<Color, std::vector<SDL_Texture *>> balls_textures_;
  std::vector<SDL_Texture *> background_texture_;

  std::vector<SDL_Texture *> extra_life_texture_;
  std::vector<SDL_Texture *> multi_ball_texture_;
  std::vector<SDL_Texture *> speed_up_texture_;
  std::vector<texture_ptr> bonuses_textures_;

  std::vector<SDL_Texture *> triangle_textures_;

public:
  Assets() {}
  inline Assets(SDL_Renderer &renderer) { loadTextures(renderer); }
  inline texture_ptr getRectangleTexture(Color color) {
    return std::make_shared<std::vector<SDL_Texture *>>(
        rectangles_textures_[color]);
  }
  inline texture_ptr getBallTexture(Color color) {
    return std::make_shared<std::vector<SDL_Texture *>>(balls_textures_[color]);
  }

  inline texture_ptr getBackgroundTexture() {
    return std::make_shared<std::vector<SDL_Texture *>>(background_texture_);
  }

  inline std::shared_ptr<std::vector<texture_ptr>> getBonusesTextures() {
    return std::make_shared<std::vector<texture_ptr>>(bonuses_textures_);
  }

  inline texture_ptr getTriangleTextures() {
    return std::make_shared<std::vector<SDL_Texture*>>(triangle_textures_);
  }

private:
  void loadTextures(SDL_Renderer &renderer);
  SDL_Texture *loadTexture(const char *path, SDL_Renderer &renderer);
};

#endif