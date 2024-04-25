#ifndef CLOCK_H
#define CLOCK_H

#include <SDL_timer.h>

class Clock {
private:
  Uint64 last_ = 0;
  Uint64 now_ = SDL_GetPerformanceCounter();

public:
  Uint64 time_elapsed; // time between now and last in milliseconds
  inline void tick() {
    last_ = now_;
    now_ = SDL_GetPerformanceCounter();
    time_elapsed =
        ((now_ - last_) * 1000) / (double)SDL_GetPerformanceFrequency();
  }
};

#endif