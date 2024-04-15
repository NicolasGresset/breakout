#include "../include/SDL2Window.h"
#include <SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>
#include <utility>
#include "../include/constants.h"
#include "../include/utils.h"

SDL2Window::SDL2Window()
    : window_{nullptr}, renderer_(nullptr), screen_width_{WINDOW_WIDTH},
      screen_height_{WINDOW_HEIGHT} {}

SDL2Window::SDL2Window(int screen_width, int screen_height)
    : window_(nullptr), renderer_(nullptr), screen_width_{screen_width},
      screen_height_{screen_height} {};

void SDL2Window::initSDLObjects() {
  int code;
  code = SDL_Init(SDL_INIT_VIDEO);
  checkSDLReturnCode((code < 0));
  
  window_ = SDL_CreateWindow(
           "Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
           screen_width_, screen_height_, SDL_WINDOW_SHOWN);
  checkSDLReturnCode(window_ == nullptr);

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
  checkSDLReturnCode(renderer_ == nullptr);
}

void SDL2Window::init() {
  this->initSDLObjects();
  this->clearWindow();
}

SDL2Window::~SDL2Window() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
}

void SDL2Window::update() { SDL_RenderPresent(renderer_); }
