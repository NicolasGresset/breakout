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
  rectangles_textures_.insert(std::make_pair(
      Color::blue,
      loadTexture("textures/element_blue_rectangle.bmp", renderer)));
  rectangles_textures_.insert(std::make_pair(
      Color::green,
      loadTexture("textures/element_green_rectangle.bmp", renderer)));
  rectangles_textures_.insert(std::make_pair(
      Color::grey,
      loadTexture("textures/element_grey_rectangle.bmp", renderer)));
  rectangles_textures_.insert(std::make_pair(
      Color::purple,
      loadTexture("textures/element_purple_rectangle.bmp", renderer)));
  rectangles_textures_.insert(std::make_pair(
      Color::red, loadTexture("textures/element_red_rectangle.bmp", renderer)));
  rectangles_textures_.insert(std::make_pair(
      Color::yellow,
      loadTexture("textures/element_yellow_rectangle.bmp", renderer)));

  // Load balls
  balls_textures_.insert(std::make_pair(
      Color::blue, loadTexture("textures/ball_blue.bmp", renderer)));
}
