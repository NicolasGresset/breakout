#include "../include/assets.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <iostream>

SDL_Texture *Assets::loadTexture(const char *path) {
  SDL_Surface *surface = SDL_LoadBMP(path);

  if (!surface) {
    std::cerr << "unable to load image : " << path << std::endl;
    exit(EXIT_FAILURE);
  }

  SDL_Texture *texture;
  if ((texture = SDL_CreateTextureFromSurface(renderer_, surface)) == nullptr) {
    std ::cerr << std::string{SDL_GetError()} << std::endl;
    exit(EXIT_FAILURE);
  }

  SDL_FreeSurface(surface);
  return texture;
}

void Assets::loadTextures(SDL_Renderer *renderer) {
  renderer_ = renderer;
  // Load rectangles
  rectangles_textures_.insert(std::make_pair(
      Color::blue, loadTexture("textures/element_blue_rectangle.bmp")));
  rectangles_textures_.insert(std::make_pair(
      Color::green, loadTexture("textures/element_green_rectangle.bmp")));
  rectangles_textures_.insert(std::make_pair(
      Color::grey, loadTexture("textures/element_grey_rectangle.bmp")));
  rectangles_textures_.insert(std::make_pair(
      Color::purple, loadTexture("textures/element_purple_rectangle.bmp")));
  rectangles_textures_.insert(std::make_pair(
      Color::red, loadTexture("textures/element_red_rectangle.bmp")));
  rectangles_textures_.insert(std::make_pair(
      Color::yellow, loadTexture("textures/element_yellow_rectangle.bmp")));

  // Load balls
  balls_textures_.insert(
      std::make_pair(Color::blue, loadTexture("textures/ball_blue.bmp")));
}