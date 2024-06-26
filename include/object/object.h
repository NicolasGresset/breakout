#ifndef Object_H
#define Object_H

#include "utils/vector2D.h"
#include <SDL2/SDL_render.h>
#include <memory>
#include <vector>

using texture_ptr = std::shared_ptr<std::vector<SDL_Texture *>>;


/**
 * @brief An Object is a class which represents anything present in the screen
that can interact with other Objects, such as a brick and a ball for instance.

It must have a Position, a Color

This class is intended to be virtual and be specialized into Brick, Dock or Ball
 * 
 */
class Object {
protected:
  // The position of the center of the object --> any object MUST have a center
  // unambiguously defined
  Vector2D position_;
  texture_ptr texture_;

public:
  Object();
  Object(Vector2D position, texture_ptr texture);
  virtual void draw(SDL_Renderer &renderer) const = 0;

  inline void setTexture(texture_ptr texture) { texture_ = texture; }

  inline texture_ptr getTexture() { return texture_; }

  inline const Vector2D &getPosition() const { return position_; }

  // inline SDL_Texture *getTexture() { return texture_; }

  virtual inline Vector2D toUpperLeftCoords() const = 0;

  virtual ~Object(){};
};

/* Héritage virtuel pour résoudre le problème du diamant*/
class MovableObject : virtual public Object {
protected:
  Vector2D speed_;

public:
  virtual inline void move(Uint64 delta) {
    position_.x_ += speed_.x_ * delta;
    position_.y_ += speed_.y_ * delta;
  }

  MovableObject();
  MovableObject(Vector2D position, texture_ptr texture, Vector2D speed);
  MovableObject(Vector2D speed);

  inline const Vector2D &getSpeed() const { return speed_; }
  inline void setSpeed(const Vector2D speed) {
    speed_.x_ = speed.x_;
    speed_.y_ = speed.y_;
  }
};

#endif
