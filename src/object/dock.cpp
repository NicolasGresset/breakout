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
//           Vector2D{WINDOW_WIDTH / 2, WINDOW_HEIGHT - PADDING - DOCK_HEIGHT / 2},
//           texture, DOCK_WIDTH, DOCK_HEIGHT), MovableObject(Vector2D(DOCK_SPEED_X,0)) {}

Dock::Dock() : Rectangle(), MovableObject() {}

Dock::Dock(Vector2D position, double width, double height, std::shared_ptr<SDL_Texture> texture, Vector2D speed) : Rectangle(position, texture, width, height), MovableObject(speed) {}

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