#include "object/triangle.h"
#include "object/line.h"
#include "utils/utils.h"
#include <SDL_rect.h>
#include <vector>

Triangle::Triangle() : Object() {}
Triangle::Triangle(double orientation, double length)
    : Object(), orientation_(orientation), length_(length) {}

Triangle::Triangle(Vector2D position, texture_ptr texture, double orientation,
                   double length)
    : Object(position, texture), orientation_(orientation), length_(length) {}

void Triangle::draw(SDL_Renderer &renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();
  SDL_Rect destinationRect = {(int)upper_left_coords.x_,
                              (int)upper_left_coords.y_, (int)length_,
                              (int)(length_ * SQUARE_ROOT_3 / 2)};

  CHECK_SDL_RETURN_CODE(SDL_RenderCopyEx(&renderer, texture_->at(0), NULL,
                                         &destinationRect,  orientation_ * 180 / PI,
                                         NULL, SDL_FLIP_NONE) < 0);
}

std::vector<Vector2D> Triangle::getVertices() const {
  Vector2D A =
      Vector2D(position_.x_, position_.y_ - SQUARE_ROOT_3 * length_ / 4)
          .rotate(orientation_, position_);
  Vector2D B = Vector2D(position_.x_ - length_ / 2,
                        position_.y_ + SQUARE_ROOT_3 * length_ / 4)
                   .rotate(orientation_, position_);
  Vector2D C = Vector2D(position_.x_ + length_ / 2,
                        position_.y_ + SQUARE_ROOT_3 * length_ / 4)
                   .rotate(orientation_, position_);

  std::vector<Vector2D> vector;
  vector.push_back(A);
  vector.push_back(B);
  vector.push_back(C);
  return vector;
}

std::vector<Line> Triangle::getEdges() const {
  std::vector<Vector2D> vertices = this->getVertices();
  std::vector<Line> edges;
  edges.push_back(Line(vertices[0], vertices[1]));
  edges.push_back(Line(vertices[1], vertices[2]));
  edges.push_back(Line(vertices[2], vertices[0]));
  return edges;
}
