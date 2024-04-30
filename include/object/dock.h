#ifndef DOCK_H
#define DOCK_H

#include "gui/SDL2Window.h"
#include "object.h"
#include "rectangle.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>

/*
A dock is semantically close to a rectangle because of its shape but also
differs because of different methods and its ability to move. Hence, multiple
heritance shall be considered #todo
*/
class Dock : public Rectangle, public MovableObject {
private:
  int life_;

public:
  Dock();
  // Dock(SDL_Texture *texture);
  Dock(Vector2D position, double width, double height, SDL_Texture *texture,
       Vector2D spee, int life);

  void handleEvent(SDL_Event &event);

  inline const Vector2D &getPosition() const {
    return Rectangle::getPosition();
  }

  inline void draw(SDL_Renderer &renderer) const override {
    Rectangle::draw(renderer);
  }

  inline Vector2D toUpperLeftCoords() const override {
    return Rectangle::toUpperLeftCoords();
  }

  void move(Uint64 delta) override;

  inline void popLife() { life_--; }

  inline bool isAlive() const { return life_ > 0; }
};

#endif