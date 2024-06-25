#pragma once
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL.h>

enum Direction {
    DOWN,
    UP,
    RIGHT,
    LEFT
};

bool HandleEvents(SDL_Event& event, Direction& dir);
void MoveRedDot(SDL_Rect& redDot, Direction dir);

#endif
