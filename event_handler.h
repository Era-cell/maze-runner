#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL.h>
#include <chrono>
#include "globals.h"

enum Direction { UP, DOWN, LEFT, RIGHT };

bool HandleEvents(SDL_Event& event, Direction& dir, bool& boostActive);
void MoveRedDot(SDL_Rect& redDot, Direction dir, bool boostActive);

#endif // EVENT_HANDLER_H
