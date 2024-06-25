#include "renderer.h"
#include "sdl_utils.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "rectmaze.h"
#include "bfs.h"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <chrono>
#include <thread>
#include "event_handler.h"
#include "maze_handler.h"
#include "globals.h"

int wins = 0;
int streak = 0;

void DisplayMessage(SDL_Renderer* renderer, const std::string& message, float relativeX, float relativeY, SDL_Color color, int delay) {
    int x = static_cast<int>(WINDOW_WIDTH * relativeX);
    int y = static_cast<int>(WINDOW_HEIGHT * relativeY);
    DrawText(renderer, message, x, y, color, 14);
    SDL_RenderPresent(renderer);
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    SDL_RenderClear(renderer); // Clear the renderer after displaying the message
}

void RunGame(SDL_Renderer* renderer, Maze* maze, SpanningtreeAlgorithm* algorithm) {
    SDL_Event event;
    bool running = true;
    Direction dir = RIGHT;

    // Calculate center of the maze in terms of maze cells
    int centerX = MAZE_WIDTH / 2;
    int centerY = MAZE_HEIGHT / 2;

    // Calculate initial position of red dot in screen coordinates
    SDL_Rect redDot{
        centerX * DISPLAY_SCALE + SHIFT,
        centerY * DISPLAY_SCALE + SHIFT,
        DOT_SIZE,
        DOT_SIZE
    };

    bool initialPosition = true; // Flag to track initial position setup

    auto regenerateMaze = [&]() {
        maze->InitialiseGraph();
        maze->GenerateMaze(algorithm);
        auto lines = maze->GetLines();

        if (initialPosition) {
            // Remove top-left and bottom-right edges for initial position
            SDL_Rect redDotTopLeft{
                centerX * DISPLAY_SCALE + SHIFT - 1,
                centerY * DISPLAY_SCALE + SHIFT - 1,
                DOT_SIZE,
                DOT_SIZE
            };
            RemoveCubeEdges(redDotTopLeft, lines, MAZE_WIDTH, MAZE_HEIGHT, SHIFT, DISPLAY_SCALE);

            initialPosition = false; // Set initial position flag to false after setup
        }

        RemoveCubeEdges(redDot, lines, MAZE_WIDTH, MAZE_HEIGHT, SHIFT, DISPLAY_SCALE);

        DrawMaze(renderer, lines, redDot, DISPLAY_SCALE, SHIFT, wins, streak);
        SDL_Color readyColor = { 255, 165, 0, 255 }; // Orange color for "Ready!"
        DisplayMessage(renderer, "Ready!", 0.5, 0.5, readyColor, 1); // Display "Ready!" message for 1 second
        DrawMaze(renderer, lines, redDot, DISPLAY_SCALE, SHIFT, wins, streak); // Redraw the maze
        SDL_Color goColor = { 0, 255, 0, 255 }; // Green color for "Go!"
        DisplayMessage(renderer, "Go!", 0.5, 0.5, goColor, 1);    // Display "Go!" message for 1 second
        return lines;
        };

    auto lines = regenerateMaze();
    auto lastRegenerateTime = std::chrono::system_clock::now();

    auto [endRow, endColumn] = static_cast<RectangularMaze*>(maze)->GetEndVertexCoordinates();
    int endX = endColumn * DISPLAY_SCALE + SHIFT; // Convert to screen coordinates
    int endY = endRow * DISPLAY_SCALE + SHIFT; // Convert to screen coordinates

    bool gameLost = false;
    bool gameWon = false;

    while (running) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_LEFT:
                    dir = LEFT;
                    break;
                case SDLK_RIGHT:
                    dir = RIGHT;
                    break;
                case SDLK_UP:
                    dir = UP;
                    break;
                case SDLK_DOWN:
                    dir = DOWN;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }

        MoveRedDot(redDot, dir);

        if (IsCollision(redDot, lines, SHIFT, DISPLAY_SCALE)) {
            gameLost = true;
            streak = 0; // Reset streak on loss
            running = false;
        }

        if (IsExitReached(redDot, MAZE_WIDTH, MAZE_HEIGHT, SHIFT, DISPLAY_SCALE)) {
            gameWon = true;
            running = false;
            wins++;
            streak++;
        }

        auto now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - lastRegenerateTime;
        if (elapsed_seconds.count() >= 10) {
            lines = regenerateMaze();
            lastRegenerateTime = now;
            std::tie(endRow, endColumn) = static_cast<RectangularMaze*>(maze)->GetEndVertexCoordinates();
            endX = endColumn * DISPLAY_SCALE + SHIFT;
            endY = endRow * DISPLAY_SCALE + SHIFT;
        }

        DrawMaze(renderer, lines, redDot, DISPLAY_SCALE, SHIFT, wins, streak);

        SDL_Delay(10); // Delay to control the red dot's movement speed
    }

    SDL_Color textColor;

    if (gameLost) {
        textColor = { 255, 0, 0, 255 }; // Red color for losing message
    }
    else if (gameWon) {
        textColor = { 0, 255, 0, 255 }; // Green color for winning message
    }
    else {
        textColor = { 255, 255, 255, 255 }; // Default white color for other messages
    }

    if (gameLost) {
        DrawText(renderer, "You got caught! Press any key to start again.", 0.25 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT, textColor, 14);
    }
    else if (gameWon) {
        DrawText(renderer, "Congratulations! Press any key to start again.", 0.25 * WINDOW_WIDTH, 0.5 * WINDOW_HEIGHT, textColor, 14);
    }

    SDL_RenderPresent(renderer); // Display the end game message

    // Wait for any key press to restart the game
    SDL_Event e;
    bool waitingForKey = true;
    while (waitingForKey) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                waitingForKey = false;
            }
        }
    }
}
