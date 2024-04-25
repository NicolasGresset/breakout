#ifndef DOCK_H
#define DOCK_H

#include "SDL2Window.h"
#include "object.h"
#include "rectangle.h"
#include "vector2D.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>

/*
A dock is semantically close to a rectangle because of its shape but also
differs because of different methods and its ability to move. Hence, multiple
heritance shall be considered #todo
*/
class Dock : public Rectangle, public MovableObject {

public:
  Dock(SDL_Texture *texture = nullptr);

  void handleEvent(SDL_Event &event);

  inline const Vector2D &getPosition() const {
    return Rectangle::getPosition();
  }

  inline void draw(SDL_Renderer *renderer) const { Rectangle::draw(renderer); }

  inline Vector2D toUpperLeftCoords() const {
    return Rectangle::toUpperLeftCoords();
  }

  inline void setTexture(SDL_Texture *texture) {
    Rectangle::setTexture(texture);
  }
};

#endif