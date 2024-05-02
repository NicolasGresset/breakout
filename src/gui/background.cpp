#include "gui/background.h"
#include "utils/utils.h"
#include <SDL_render.h>

ElementBackground::ElementBackground(
    std::shared_ptr<std::vector<SDL_Texture *>> background_texture,
    int screen_width, int screen_height)
    : background_texture_(background_texture), screen_width_(screen_width),
      screen_height_(screen_height) {
  center_ = {screen_width_ / 2, screen_height_ / 2};
  rect_ = {0, 0, screen_width_, screen_height_};
}

void ElementBackground::draw(SDL_Renderer &renderer) {
  CHECK_SDL_RETURN_CODE(SDL_RenderCopyEx(&renderer, current_texture_, NULL,
                                         &rect_, getAngle(), &center_,
                                         SDL_FLIP_NONE) < 0);

  updateFrames();
}

void ElementBackground::updateFrames() {
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
        current_frame_++;
      }
    }
  }
}

void ElementBackground::speedUp(double amount) {
  ASSERT_FN(amount >= 0 && amount <= 100, [&]() {
    std::cerr << "Amount should be a percentage between 0 and 100 and it is "
              << amount << std::endl;
  });

  reset_threshold_ *= (1 - amount / 100);
}