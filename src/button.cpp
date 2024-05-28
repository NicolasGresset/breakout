#include "button.h"
#include "object/rectangle.h"
#include "utils/utils.h"
#include <SDL2/SDL_render.h>
#include <cstddef>
#include <iostream>

Button::Button(Vector2D position, double width, double height, std::string text,
               bool clickable, SDL_Color color, TTF_Font *font,
               std::function<void()> on_click)
    : Object(position, nullptr), Rectangle(width, height), text_(text),
      clickable_(clickable), color_(color), font_(font), on_click_(on_click) {
  position_.print();
}

void Button::draw(SDL_Renderer &renderer) const {
  // todo add logic for hovering

  // Render text inside button
  SDL_Surface *surface = TTF_RenderText_Solid(font_, text_.c_str(), color_);
  CHECK_SDL_RETURN_CODE(surface == nullptr);

  SDL_Texture *texture = SDL_CreateTextureFromSurface(&renderer, surface);
  CHECK_SDL_RETURN_CODE(texture == nullptr);
  SDL_FreeSurface(surface);

  SDL_Rect textRect = {static_cast<int>(position_.x_ - width_ / 2),
                       static_cast<int>(position_.y_ - height_ / 2),
                       static_cast<int>(width_), static_cast<int>(height_)};

  CHECK_SDL_RETURN_CODE(SDL_RenderCopy(&renderer, texture, NULL, &textRect) <
                        0);
}

bool Button::isClicked(int mouseX, int mouseY) {
  int x = static_cast<int>(position_.x_ - width_ / 2);
  int y = static_cast<int>(position_.y_ - height_ / 2);
  return (mouseX >= x && mouseX < x + width_ && mouseY >= y &&
          mouseY < y + height_);
}

void Button::handleEvents(SDL_Event &event) {
  if (!(event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN ||
        event.type == SDL_MOUSEBUTTONUP)) {
    return;
  }

  int x, y;
  SDL_GetMouseState(&x, &y);
  if (!isClicked(x, y)) {
    is_hovered_ = false;
    return;
  }

  switch (event.type) {
  case SDL_MOUSEMOTION:
    is_hovered_ = true;
    break;
  case SDL_MOUSEBUTTONDOWN:
    if (event.button.button == SDL_BUTTON_LEFT) {
      on_click_();
    }
    break;
  }
}

void Button::update() {
  // todo faire cette fonction si besoin
}