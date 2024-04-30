#include "gui/background.h"
#include "utils/utils.h"
#include <SDL_render.h>

Background::Background(
    std::shared_ptr<std::vector<SDL_Texture *>> background_texture,
    int screen_width, int screen_height)
    : background_texture_(background_texture), screen_width_(screen_width),
      screen_height_(screen_height) {}

void Background::draw(SDL_Renderer &renderer) {
  SDL_Texture *current_texture = background_texture_->at(current_frame_);
  int code;
  SDL_Rect rect{0, 0, screen_width_, screen_height_};
  code = SDL_RenderCopy(&renderer, current_texture, nullptr, &rect);
  CHECK_SDL_RETURN_CODE(code < 0);

  updateFrames();
}

void Background::updateFrames() {
  if (++nb_frames_ >= same_frame_) {
    nb_frames_ = 0;
    if (raising_values) {
      if (++current_frame_ >
          static_cast<int>(background_texture_->size()) - 1) {
        current_frame_--;
        raising_values = false;
      }
    } else {
      if (--current_frame_ < 0) {
        raising_values = true;
        current_frame_ = 1;
      }
    }
  }
}