#include "object/dock.h"
#include "utils/constants.h"
#include "utils/vector2D.h"

Dock::Dock() : Object(), Rectangle(), MovableObject(), life_() {}

Dock::Dock(Vector2D position, double width, double height, texture_ptr texture,
           Vector2D speed, int life)
    : Object(position, texture), Rectangle(width, height), MovableObject(speed),
      life_(life) {}

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

void Dock::reset() {
  position_.x_ = static_cast<double>(WINDOW_WIDTH) / 2;
  position_.y_ = static_cast<double>(WINDOW_HEIGHT - PADDING) -
                 static_cast<double>(DOCK_HEIGHT) / 2;
}