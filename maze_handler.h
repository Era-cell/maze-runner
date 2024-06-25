#ifndef MAZE_HANDLER_H
#define MAZE_HANDLER_H

#include <vector>
#include <tuple>
#include <string>
#include <SDL.h>
#include "rectmaze.h"
#include "bfs.h"

void RemoveCubeEdges(SDL_Rect& redDot, std::vector<std::tuple<std::string, std::string, std::string, std::string>>& lines, int mazeWidth, int mazeHeight, int shift, int scale);
bool IsCollision(SDL_Rect redDot, const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& lines, int shift, int scale);
bool IsExitReached(SDL_Rect redDot, int mazeWidth, int mazeHeight, int shift, int scale);

#endif
