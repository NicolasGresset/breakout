#ifndef CLOCK_H
#define CLOCK_H

#include <SDL_stdinc.h>
#include <SDL_timer.h>

// todo make pause work !
/**
 * @brief Convenient class to measure time passing
 *
 */
class Clock {
private:
  Uint64 last_ = 0;
  Uint64 now_ = SDL_GetPerformanceCounter();

  bool is_paused = false;
  Uint64 paused_time_;
  Uint64 pause_start_;

public:
  Uint64 time_elapsed; // time between now and last in milliseconds
  inline void tick() {
    last_ = now_;
    now_ = SDL_GetPerformanceCounter();
    time_elapsed =
        ((now_ - last_) * 1000) / (double)SDL_GetPerformanceFrequency();
    if (is_paused) {
      time_elapsed -= paused_time_;
      is_paused = false;
    }
  }

  inline double getFPS() { return 1000.0 / time_elapsed; }

  inline Uint64 getTotalTime() const { return now_; }

  inline void pause() {
    pause_start_ = SDL_GetPerformanceCounter();
    is_paused = true;
  }

  inline void resume() {
    paused_time_ = (SDL_GetPerformanceCounter() - pause_start_) * 1000 /
                   (double)SDL_GetPerformanceFrequency();
  }
};

#endif