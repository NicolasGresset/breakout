#include "button.h"
#include "utils/utils.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <cstddef>
#include <iostream>

Button::Button(Vector2D position, SDL_Color color, double width, double height,
               std::string text)
    : Object(position, NULL), color_(color), width_(width), height_(height),
      text_(text){};

// Button::Button() : Object(Vector2D{0, 0}, nullptr){};

void Button::draw(SDL_Renderer *renderer) const {
  Vector2D upper_left_coords = this->toUpperLeftCoords();
  SDL_Rect destButton = {(int)upper_left_coords.x_, (int)upper_left_coords.y_,
                         (int)width_, (int)height_};
  int code;

  TTF_Font *font = TTF_OpenFont("./font/hershey.ttf", 24);
  CHECK_SDL_RETURN_CODE(!font);
  // Render text inside button
  SDL_Surface *surface = TTF_RenderText_Solid(font, text_.c_str(), color_);
  CHECK_SDL_RETURN_CODE(!surface);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  CHECK_SDL_RETURN_CODE(!texture);

  SDL_Rect textRect = {(int)(upper_left_coords.x_ + (width_ - surface->w) / 2),
                       (int)(upper_left_coords.y_ + (height_ - surface->h) / 2),
                       static_cast<int>(width_), static_cast<int>(height_)};

  TTF_CloseFont(font);
  SDL_FreeSurface(surface);

  code = SDL_RenderCopy(renderer, texture, NULL, &textRect);
  CHECK_SDL_RETURN_CODE(code < 0);
}
