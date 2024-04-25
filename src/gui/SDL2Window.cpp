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
#include <cstdlib>
#include <iostream>
#include <utility>

SDL2Window::SDL2Window()
    : screen_width_{WINDOW_WIDTH}, screen_height_{WINDOW_HEIGHT},
      window_{nullptr, SDL_DestroyWindow},
      renderer_(nullptr, SDL_DestroyRenderer) {}

SDL2Window::SDL2Window(int screen_width, int screen_height)
    : screen_width_{screen_width}, screen_height_{screen_height},
      window_{nullptr, SDL_DestroyWindow},
      renderer_(nullptr, SDL_DestroyRenderer) {}
{};

void SDL2Window::initSDLObjects() {
  int code;
  code = SDL_Init(SDL_INIT_VIDEO);
  CHECK_SDL_RETURN_CODE((code < 0));

  // Init TTF
  code = TTF_Init();
  CHECK_SDL_RETURN_CODE((code < 0));

  window_.reset(SDL_CreateWindow("Breakout", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, screen_width_,
                                 screen_height_, SDL_WINDOW_SHOWN));
  CHECK_SDL_RETURN_CODE(window_.get() == nullptr);

  renderer_.reset(
      SDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED));
  CHECK_SDL_RETURN_CODE(renderer_.get() == nullptr);
}

void SDL2Window::init() {
  this->initSDLObjects();
  this->clearWindow();
}

SDL2Window::~SDL2Window() {
  if (window_.get() != nullptr) {
    SDL_DestroyWindow(window_.get());
  }
  if (renderer_.get() != nullptr) {
    SDL_DestroyRenderer(renderer_.get());
  }
  TTF_Quit(); // Quit ttf
  SDL_Quit();
}

void SDL2Window::update() { SDL_RenderPresent(renderer_.get()); }
