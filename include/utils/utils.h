#ifndef UTILS_H
#define UTILS_H

#include <SDL_error.h>
#include <cstdlib>
#include <iostream>

/*
Wrapper to checkSDLReturnCode to pass file and line number
*/
#define CHECK_SDL_RETURN_CODE(code) checkSDLReturnCode(code, __FILE__, __LINE__)

/**
Print SDL Error if condition code is true
This function should only be called thanks to the wrapper CHECK_SDL_RETURN_CODE
*/
inline void checkSDLReturnCode(bool code, std::string file, int line) {
  if (code) {
    std::cerr << file << ":" << line
              << " : SDL_Error : " << std::string{SDL_GetError()} << std::endl;
    exit(EXIT_FAILURE);
  }
}

#endif