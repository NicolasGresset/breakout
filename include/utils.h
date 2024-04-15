#ifndef UTILS_H
#define UTILS_H

#include <SDL_error.h>
#include <cstdlib>
#include <iostream>

/**
Print SDL Error if condition code is true
*/
inline void checkSDLReturnCode(bool code){
    if (code){
        std::cerr << "SDL_Error : " << std::string{SDL_GetError()} << std::endl;
        exit(EXIT_FAILURE); 
    }
}

#endif