#include "event_handler.h"

bool HandleEvents(SDL_Event& event, Direction& dir) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        else if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_UP) {
                dir = UP;
            }
            else if (event.key.keysym.sym == SDLK_DOWN) {
                dir = DOWN;
            }
            else if (event.key.keysym.sym == SDLK_RIGHT) {
                dir = RIGHT;
            }
            else if (event.key.keysym.sym == SDLK_LEFT) {
                dir = LEFT;
            }
        }
    }
    return true;
}

void MoveRedDot(SDL_Rect& redDot, Direction dir) {
    if (dir == UP) {
        redDot.y -= 1;
    }
    else if (dir == DOWN) {
        redDot.y += 1;
    }
    else if (dir == LEFT) {
        redDot.x -= 1;
    }
    else {
        redDot.x += 1;
    }

    if (redDot.x < 0) {
        redDot.x = 0;
    }
    else if (redDot.x > 800 - redDot.w) {
        redDot.x = 800 - redDot.w;
    }
    if (redDot.y < 0) {
        redDot.y = 0;
    }
    else if (redDot.y > 600 - redDot.h) {
        redDot.y = 600 - redDot.h;
    }
}
