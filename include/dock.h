#ifndef DOCK_H
#define DOCK_H

#include "SDL2Window.h"
#include "brick.h"
#include "vector2D.h"
#include <SDL_render.h>


/*
A dock is semantically close to a rectangle because of its shape but also differs
because of different methods and its ability to move
Hence, multiple heritance shall be considered
#todo
*/
class Dock : public Object {
public:
  Dock(SDL_Texture* texture = nullptr);
  void draw(SDL_Renderer *renderer) const override;
};

#endif