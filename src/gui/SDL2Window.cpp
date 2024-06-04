#include "gui/SDL2Window.h"
#include "utils/constants.h"
#include "utils/utils.h"
#include <SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>

SDL2Window::SDL2Window()
    : screen_width_{WINDOW_WIDTH}, screen_height_{WINDOW_HEIGHT},
      window_{nullptr}, renderer_(nullptr) {
  initSDLObjects();
}

SDL2Window::SDL2Window(int screen_width, int screen_height)
    : screen_width_{screen_width}, screen_height_{screen_height},
      window_{nullptr}, renderer_(nullptr) {
  initSDLObjects();
}

void SDL2Window::initSDLObjects() {
  int code;
  code = SDL_Init(SDL_INIT_VIDEO);
  CHECK_SDL_RETURN_CODE((code < 0));

  // Init TTF
  code = TTF_Init();
  CHECK_SDL_RETURN_CODE((code < 0));

  window_ = SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED,
                             SDL_WINDOWPOS_UNDEFINED, screen_width_,
                             screen_height_, SDL_WINDOW_SHOWN);
  CHECK_SDL_RETURN_CODE(window_ == nullptr);

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  CHECK_SDL_RETURN_CODE(renderer_ == nullptr);

  DEBUG_MSG("Succesfully initialized SDL objects");
}

SDL2Window::~SDL2Window() {
  if (window_ != nullptr) {
    SDL_DestroyWindow(window_);
  }
  if (renderer_ != nullptr) {
    SDL_DestroyRenderer(renderer_);
  }
  TTF_Quit(); // Quit ttf
  SDL_Quit();
}
