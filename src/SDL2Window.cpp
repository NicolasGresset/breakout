#include "../include/SDL2Window.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_video.h>
#include <cstdlib>
#include <iostream>

SDL2Window::SDL2Window()
    : window_{nullptr}, screen_surface_{nullptr}, screen_width_{650},
      screen_height_{480} {}

SDL2Window::SDL2Window(int screen_width, int screen_height)
    : window_(nullptr), screen_surface_(nullptr), screen_width_{screen_width},
      screen_height_{screen_height} {};

void SDL2Window::init() {
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

  screen_surface_ =
      SDL_GetWindowSurface(window_); // could return NULL on failure
  SDL_FillRect(screen_surface_, NULL,
               SDL_MapRGB(screen_surface_->format, 0xFF, 0xFF, 0xFF));

  SDL_UpdateWindowSurface(window_);
}

SDL2Window::~SDL2Window() {
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void SDL2Window::update(){
    SDL_UpdateWindowSurface(window_);
}