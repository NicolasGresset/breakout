#ifndef Object_H
#define Object_H

#include "utils/vector2D.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL_stdinc.h>

/*
An Object is a class which represents anything present in the screen that can
interact with other Objects, such as a brick and a ball for instance.

It must have a Position, a Color

This class is intended to be virtual and be specialized into Brick, Dock or Ball
*/
class Object {
protected:
  // The position of the center of the object --> any object MUST have a center
  // unambiguously defined
  Vector2D position_;
  SDL_Texture *texture_;

public:
  Object();
  Object(Vector2D position, SDL_Texture *texture);
  virtual void draw(SDL_Renderer *renderer) const = 0;

  inline void setTexture(SDL_Texture *texture) { texture_ = texture; }

  inline const Vector2D &getPosition() const { return position_; }

  virtual inline Vector2D toUpperLeftCoords() const = 0;

  virtual ~Object(){};
};

class MovableObject : public Object {
protected:
  Vector2D speed_;

public:
  inline void move(Uint64 delta) {
    position_.x_ += speed_.x_ * delta;
    position_.y_ += speed_.y_ * delta;
  }

  MovableObject();
  MovableObject(Vector2D position, SDL_Texture *texture, Vector2D speed);
};

#endif