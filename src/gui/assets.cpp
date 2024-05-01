#include "gui/assets.h"
#include "utils/utils.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <iostream>

SDL_Texture *Assets::loadTexture(const char *path, SDL_Renderer &renderer) {
  SDL_Surface *surface = SDL_LoadBMP(path);

  if (!surface) {
    std::cerr << "unable to load image : " << path << std::endl;
    exit(EXIT_FAILURE);
  }

  SDL_Texture *texture;
  texture = SDL_CreateTextureFromSurface(&renderer, surface);
  CHECK_SDL_RETURN_CODE(texture == nullptr);

  SDL_FreeSurface(surface);
  return texture;
}

void Assets::loadTextures(SDL_Renderer &renderer) {
  // Load rectangles
  rectangles_textures_.insert(
      std::make_pair(Color::blue, std::vector<SDL_Texture *>()));
  rectangles_textures_[Color::blue].push_back(
      loadTexture("textures/element_blue_rectangle.bmp", renderer));

  rectangles_textures_.insert(
      std::make_pair(Color::green, std::vector<SDL_Texture *>()));
  rectangles_textures_[Color::green].push_back(
      loadTexture("textures/element_green_rectangle.bmp", renderer));

  rectangles_textures_.insert(
      std::make_pair(Color::grey, std::vector<SDL_Texture *>()));
  rectangles_textures_[Color::grey].push_back(
      loadTexture("textures/element_grey_rectangle.bmp", renderer));

  rectangles_textures_.insert(
      std::make_pair(Color::purple, std::vector<SDL_Texture *>()));
  rectangles_textures_[Color::purple].push_back(
      loadTexture("textures/element_purple_rectangle.bmp", renderer));

  rectangles_textures_.insert(
      std::make_pair(Color::red, std::vector<SDL_Texture *>()));
  rectangles_textures_[Color::red].push_back(
      loadTexture("textures/element_red_rectangle.bmp", renderer));

  rectangles_textures_.insert(
      std::make_pair(Color::yellow, std::vector<SDL_Texture *>()));
  rectangles_textures_[Color::yellow].push_back(
      loadTexture("textures/element_yellow_rectangle.bmp", renderer));

  // Load balls
    balls_textures_.insert(
      std::make_pair(Color::blue, std::vector<SDL_Texture *>()));
  balls_textures_[Color::blue].push_back(
      loadTexture("textures/ball_blue.bmp", renderer));

  // load background
  for (int i(2); i < 12; i++) {
    std::string background_name =
        "textures/mandelbrot" + std::to_string(i) + ".bmp";
    background_texture_.push_back(
        loadTexture(background_name.c_str(), renderer));
  }
}
