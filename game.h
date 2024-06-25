#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <string>
#include "maze.h"
#include "renderer.h"
#include "bfs.h"

// Function declaration for displaying a message on the screen
void DisplayMessage(SDL_Renderer* renderer, const std::string& message, float relativeX, float relativeY, SDL_Color color, int delay);

// Function declaration for running the game
void RunGame(SDL_Renderer* renderer, Maze* maze, SpanningtreeAlgorithm* algorithm);

#endif // GAME_H
