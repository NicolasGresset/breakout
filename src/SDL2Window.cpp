#include "../include/SDL2Window.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>
#include <utility>

SDL2Window::SDL2Window()
    : window_{nullptr}, renderer_(nullptr), screen_width_{800},
      screen_height_{500} {}

SDL2Window::SDL2Window(int screen_width, int screen_height)
    : window_(nullptr), renderer_(nullptr), screen_width_{screen_width},
      screen_height_{screen_height} {};

void SDL2Window::initSDLObjects() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: "
              << std::string{SDL_GetError()} << std::endl;
    exit(EXIT_FAILURE);
  }

  if ((window_ = SDL_CreateWindow(
           "Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
           screen_width_, screen_height_, SDL_WINDOW_SHOWN)) == nullptr) {
    std::cerr << "Window could not be created! SDL_Error: "
              << std::string{SDL_GetError()} << std::endl;
    exit(EXIT_FAILURE);
  }

  if ((renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)) ==
      nullptr) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    exit(EXIT_FAILURE);
  }
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



// void SDL2Window::foo() {
//   SDL_Rect destinationRect = {100, 100, 70, 70}; // x, y, width, height
//   SDL_RenderClear(renderer_);
//   SDL_RenderCopy(renderer_, assets_.getBallTexture(Color::blue), NULL,
//                  &destinationRect);
// }