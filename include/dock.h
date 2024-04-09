#ifndef DOCK_H
#define DOCK_H

#include "SDL2Window.h"
#include "object.h"
#include "vector2D.h"
#include <SDL_events.h>
#include <SDL_render.h>

/*
A dock is semantically close to a rectangle because of its shape but also
differs because of different methods and its ability to move. Hence, multiple
heritance shall be considered #todo
*/
class Dock : public Object {
private:
  double width_;
  double height_;

  Vector2D speed_;

public:
  Dock(SDL_Texture *texture = nullptr);
  void draw(SDL_Renderer *renderer) const override;

  inline Vector2D toUpperLeftCoords() const {
    return Vector2D(position_.getX() - width_ / 2,
                    position_.getY() - height_ / 2);
  }

  void handleEvent(SDL_Event& event);

  /*
  Update Dock's position_ accordingly to its speed
*/
  void move() ;

};

#endif