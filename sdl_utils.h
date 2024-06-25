#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <SDL.h>

bool InitSDL(int width, int height);
void CleanupSDL();
SDL_Renderer* CreateRenderer();

#endif
