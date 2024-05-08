#include "button.h"
#include "utils/utils.h"
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <iostream>

Button::Button(Vector2D position,
               double width,
               double height,
               std::string text,
               bool clickable,
               SDL_Color color)
    : Object(position, NULL),  width_(width), height_(height),
      text_(text), clickable_(clickable), color_(color){};

// Button::Button() : Object(Vector2D{0, 0}, nullptr){};

void Button::draw(SDL_Renderer &renderer) const {
  int code;

  TTF_Font *font = TTF_OpenFont("./font/hershey.ttf", 50);
  CHECK_SDL_RETURN_CODE(!font);
  // Render text inside button
  SDL_Surface *surface = TTF_RenderText_Solid(font, text_.c_str(), color_);
  CHECK_SDL_RETURN_CODE(!surface);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(&renderer, surface);
  CHECK_SDL_RETURN_CODE(!texture);

  SDL_Rect textRect = {static_cast<int>(position_.x_ - width_/2) , static_cast<int>(position_.y_ - height_/2),
                       static_cast<int>(width_), static_cast<int>(height_)};

  TTF_CloseFont(font);
  SDL_FreeSurface(surface);

  code = SDL_RenderCopy(&renderer, texture, NULL, &textRect);
  CHECK_SDL_RETURN_CODE(code < 0);
}

bool Button::isClicked(int mouseX, int mouseY) {
    int x = static_cast<int>(position_.x_ - width_/2);
    int y = static_cast<int>(position_.y_ - height_/2);
    return (mouseX >= x && mouseX < x + width_ &&
            mouseY >= y && mouseY < y + height_);
}
