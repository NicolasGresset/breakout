#include "../include/dock.h"
#include "../include/constants.h"
#include "vector2D.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <iostream>

Dock::Dock(SDL_Texture *texture)
    : Rectangle(
          Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT - PADDING - DOCK_HEIGHT / 2},
          texture, DOCK_WIDTH, DOCK_HEIGHT) {}

void Dock::handleEvent(SDL_Event &event) {

  if (event.type == SDL_KEYDOWN) {
    if (event.key.keysym.sym == SDLK_RIGHT) {
      speed_.x_ = DOCK_SPEED_X;
    } else if (event.key.keysym.sym == SDLK_LEFT) {
      speed_.x_ = -DOCK_SPEED_X;
    }
  } else if (event.type == SDL_KEYUP) {
    speed_.x_ = 0;
  }
}

void Dock::move() {
  position_.x_ += speed_.x_;
  position_.y_ += speed_.y_;
}