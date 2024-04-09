#include "../include/dock.h"
#include "../include/constants.h"
#include "vector2D.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <iostream>

Dock::Dock(SDL_Texture *texture)
    : Object(
          Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT - PADDING - DOCK_HEIGHT / 2},
          texture),
      width_(DOCK_WIDTH), height_(DOCK_HEIGHT) {}

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

void Dock::handleEvent(SDL_Event &event) {

  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_RIGHT) {
      speed_.setX(DOCK_SPEED_X);
    } else if (event.key.keysym.sym == SDLK_LEFT) {
      speed_.setX(-DOCK_SPEED_X);
    }
  } else if (event.type == SDL_KEYUP) {
    speed_.setX(0);
  }
}

void Dock::move() {
  position_.setX(position_.getX() + speed_.getX());
  position_.setY(position_.getY() + speed_.getY());
}