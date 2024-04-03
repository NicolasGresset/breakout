#include "../include/SDL2Window.h"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_video.h>
#include <cstddef>
#include <cstdlib>
#include <iostream>

SDL2Window::SDL2Window()
    : window_{nullptr}, renderer_(nullptr), screen_width_{650},
      screen_height_{480} {}

SDL2Window::SDL2Window(int screen_width, int screen_height)
    : window_(nullptr), renderer_(nullptr), screen_width_{screen_width},
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

  if ((renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED)) ==
      nullptr) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

SDL2Window::~SDL2Window() {
  SDL_DestroyWindow(window_);
  SDL_DestroyRenderer(renderer_);
  SDL_Quit();
}

void SDL2Window::update() { SDL_RenderPresent(renderer_); }

void SDL2Window::drawCirle(double centerX, double centerY, double radius) {

  double x = radius - 1;
  int y = 0;
  int dx = 1;
  int dy = 1;
  int err = dx - (int(radius) << 1);

  while (x >= y) {
    SDL_RenderDrawPoint(renderer_, centerX + x, centerY + y);
    SDL_RenderDrawPoint(renderer_, centerX + y, centerY + x);
    SDL_RenderDrawPoint(renderer_, centerX - y, centerY + x);
    SDL_RenderDrawPoint(renderer_, centerX - x, centerY + y);
    SDL_RenderDrawPoint(renderer_, centerX - x, centerY - y);
    SDL_RenderDrawPoint(renderer_, centerX - y, centerY - x);
    SDL_RenderDrawPoint(renderer_, centerX + y, centerY - x);
    SDL_RenderDrawPoint(renderer_, centerX + x, centerY - y);

    if (err <= 0) {
      y++;
      err += dy;
      dy += 2;
    }
    if (err > 0) {
      x--;
      dx += 2;
      err += dx - (int(radius) << 1);
    }
  }
}
