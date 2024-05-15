#include "gui/assets.h"
#include "utils/utils.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <iostream>
#include <memory>
#include <vector>

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
  for (int i(1); i < 1; i++) {
    std::string background_name =
        "textures/mandelbrot" + std::to_string(i) + ".bmp";
    background_texture_.push_back(
        loadTexture(background_name.c_str(), renderer));
  }

  // load bonuses textures
  extra_life_texture_.push_back(loadTexture("textures/life.bmp", renderer));
  multi_ball_texture_.push_back(
      loadTexture("textures/multi_ball.bmp", renderer));
  speed_up_texture_.push_back(loadTexture("textures/speed.bmp", renderer));

  bonuses_textures_.push_back(
      std::make_shared<std::vector<SDL_Texture *>>(extra_life_texture_));
  bonuses_textures_.push_back(
      std::make_shared<std::vector<SDL_Texture *>>(multi_ball_texture_));
  bonuses_textures_.push_back(
      std::make_shared<std::vector<SDL_Texture *>>(speed_up_texture_));

  // load triangle textures
  triangle_textures_.push_back(loadTexture("textures/triangle.bmp", renderer));
}
