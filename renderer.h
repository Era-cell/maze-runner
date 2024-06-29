#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include <string>
#include <vector>
#include <tuple>

// Function to render text using SDL_ttf
void DrawText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, int fontSize);

// Function to draw the scoreboard and instructions
void DrawScoreboard(SDL_Renderer* renderer, int wins, int streak, int maxStreak);

// Function to draw the maze, red dot, scoreboard, and instructions
void DrawMaze(SDL_Renderer* renderer, const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& lines, const SDL_Rect& redDot, int scale, int shift, int wins, int streak, int maxStreak);

#endif // RENDERER_H
