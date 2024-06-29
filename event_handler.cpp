#include "event_handler.h"
#include <chrono>

bool HandleEvents(SDL_Event& event, Direction& dir, bool& boostActive) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_LSHIFT) {
                boostActive = (event.type == SDL_KEYDOWN);
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
    }
    return true;
}

void MoveRedDot(SDL_Rect& redDot, Direction dir, bool boostActive) {
    int moveAmount = boostActive ? 3 : 1; // Move 3 blocks if boost is active, otherwise move 1 block

    if (dir == UP) {
        redDot.y -= moveAmount;
    }
    else if (dir == DOWN) {
        redDot.y += moveAmount;
    }
    else if (dir == LEFT) {
        redDot.x -= moveAmount;
    }
    else if (dir == RIGHT) {
        redDot.x += moveAmount;
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
