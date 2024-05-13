#include "bonus/bonus.h"
#include "object/brick.h"
#include "object/object.h"
#include "object/rectangle.h"
#include "utils/vector2D.h"


Bonus::Bonus() : Object(), Rectangle(), MovableObject() {}

Bonus::Bonus(texture_ptr texture, Brick &brick, int width, int height,
             Vector2D speed)
    : Object(brick.getPosition(), texture), Rectangle(width, height),
      MovableObject(speed) {}

