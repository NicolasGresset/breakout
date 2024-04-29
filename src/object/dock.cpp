#include "object/dock.h"
#include "object/object.h"
#include "object/rectangle.h"
#include "utils/constants.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_keycode.h>
#include <SDL_render.h>
#include <iostream>

// Dock::Dock(SDL_Texture *texture)
//     : Rectangle(
//           Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT - PADDING - DOCK_HEIGHT /
//           2}, texture, DOCK_WIDTH, DOCK_HEIGHT),
//           MovableObject(Vector2D(DOCK_SPEED_X,0)) {}

Dock::Dock() : Object(), Rectangle(), MovableObject() {}

Dock::Dock(Vector2D position, double width, double height, SDL_Texture *texture,
           Vector2D speed)
    : Object(position, texture), Rectangle(width, height),
      MovableObject(speed) {}

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

void Dock::move(Uint64 delta) {
  double new_x = position_.x_ + speed_.x_ * delta;
  if (new_x - width_ / 2 < 0) {
    new_x = width_ / 2;
  } else if (new_x + width_ / 2 > WINDOW_WIDTH) {
    new_x = WINDOW_WIDTH - width_ / 2;
  }
  position_.x_ = new_x;
}