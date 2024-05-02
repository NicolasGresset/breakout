#ifndef UTILS_H
#define UTILS_H

#include <SDL_error.h>
#include <iostream>

/*
Convenient wrapper to checkSDLReturnCode to pass file and line number
*/
#define CHECK_SDL_RETURN_CODE(code) checkSDLReturnCode(code, __FILE__, __LINE__)

/**
Print SDL Error if condition code is true
This function should only be called thanks to the wrapper CHECK_SDL_RETURN_CODE
*/
static inline void checkSDLReturnCode(bool code, std::string file, int line) {
  if (code) {
    std::cerr << "\033[1;34m" << file << ":"
              << "\033[1;33m" << line << ": "
              << "\033[1;31m" << std::string{SDL_GetError()} << std::endl
              << "\033[0m";
    abort();
  }
}

/*
Convenient wrapper to assertFn to pass file and line number
*/
#define ASSERT_FN(code, fn) assertFn(code, fn, __FILE__, __LINE__)

/**
Allows to smoothly check for pre-conditions assertions inside of functions
*/
template <typename Fn>
static inline void assertFn(bool expr, Fn fn, std::string file, int line) {
  if (!expr) {
    std::cerr << "\033[1;34m" << file << ":"
              << "\033[1;33m" << line << ": "
              << "\033[0m" << std::endl;
    fn();
    abort();
  }
}

#endif