#ifndef BUTTON_H
#define BUTTON_H

#include "game.h"
#include "object/rectangle.h"
#include "states/state_manager.h"
#include "utils/vector2D.h"
#include <SDL2/SDL.h>
#include <SDL_render.h>
#include <SDL_ttf.h>
#include <functional>
#include <string>

// todo modifier ce merdier, a peu pres bon sauf pour la logique du hovering
class Button : public Rectangle {

private:
  std::string text_;
  bool clickable_;
  bool is_hovered_;
  // fg_color
  SDL_Color color_;
  TTF_Font *font_;
  GameStateManager *state_manager_;
  std::function<void(GameStateManager *state_manager)> on_click_;

public:
  Button(
      Vector2D position, double width, double height, std::string text,
      bool clickable, SDL_Color color, TTF_Font *font,
      GameStateManager *state_manager = nullptr,
      std::function<void(GameStateManager *)> on_click =
          [](GameStateManager *) {});

  bool isClickable() { return clickable_; };
  bool isClicked(int mouseX, int mouseY);

  void handleEvents(SDL_Event &event);
  void draw(SDL_Renderer &renderer) const override;
  void update();

  inline void setColor(SDL_Color color) { color_ = color; };
  inline void setText(std::string text) { text_ = text; };
};

#endif
