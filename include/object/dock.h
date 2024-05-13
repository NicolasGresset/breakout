#ifndef DOCK_H
#define DOCK_H

#include "gui/SDL2Window.h"
#include "object.h"
#include "rectangle.h"
#include "utils/vector2D.h"
#include <SDL_events.h>
#include <SDL_render.h>
#include <SDL_stdinc.h>

class Dock : public Rectangle, public MovableObject {
private:
  int life_;

public:
  Dock();
  // Dock(SDL_Texture *texture);
  Dock(Vector2D position, double width, double height, texture_ptr texture,
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

  inline int getLifes() const { return life_; }

  inline void addLives(unsigned int number) { life_ += number; }
  void reset();
};

#endif
