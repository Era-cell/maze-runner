#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <tuple>

// Draws text on the screen using SDL_ttf
void DrawText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, int fontSize);

// Draws the scoreboard on the screen
void DrawScoreboard(SDL_Renderer* renderer, int wins, int streak);

// Draws the maze and the red dot on the screen
void DrawMaze(SDL_Renderer* renderer, const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& lines, const SDL_Rect& redDot, int scale, int shift, int wins, int streak);

#endif // RENDERER_H
