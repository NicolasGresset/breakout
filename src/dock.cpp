#include "../include/dock.h"
#include "../include/constants.h"
#include "vector2D.h"
#include <SDL_render.h>
#include <iostream>

Dock::Dock(SDL_Texture *texture)
    : Object(
          Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT - PADDING - DOCK_HEIGHT / 2},
          texture), width_(DOCK_WIDTH), height_(DOCK_HEIGHT) {}

void Dock::draw(SDL_Renderer *renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();
  SDL_Rect destinationRect = {(int)upper_left_coords.getX(),
                              (int)upper_left_coords.getY(), (int)width_,
                              (int)height_};

  if (SDL_RenderCopy(renderer, texture_, NULL, &destinationRect) < 0) {
    std::cerr << "unable to render rectangle brick : "
              << std::string{SDL_GetError()} << std::endl;
    exit(EXIT_FAILURE);
  }
}