#ifndef DOCK_H
#define DOCK_H

#include "SDL2Window.h"
#include "object.h"
#include "rectangle.h"
#include "vector2D.h"
#include <SDL_events.h>
#include <SDL_render.h>

/*
A dock is semantically close to a rectangle because of its shape but also
differs because of different methods and its ability to move. Hence, multiple
heritance shall be considered #todo
*/
class Dock : public Rectangle {
private:

  Vector2D speed_;

public:
  Dock(SDL_Texture *texture = nullptr);


  void handleEvent(SDL_Event& event);

  /*
  Update Dock's position_ accordingly to its speed
*/
  void move() ;

};

#endif