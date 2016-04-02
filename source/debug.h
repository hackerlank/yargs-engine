#ifndef __DEBUG_H__
#define __DEBUG_H__

#ifdef DEBUG
#include <iostream>
#include <SDL2/SDL.h>

#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#define debugSDL() fprintf(stderr, "SDL_Error %s:%d: %s\n", __FILE__, __LINE__, SDL_GetError())

#else

#define debug(M, ...)
#define debugSDL()

#endif

#endif
