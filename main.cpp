#include "renderer.h"
#include "sdl_utils.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "rectmaze.h"
#include "bfs.h"
#include <iostream>
#include "game.h"

// Global constants
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int MAZE_WIDTH = 20;
const int MAZE_HEIGHT = 20;
const int DISPLAY_SCALE = 18;
const int SHIFT = 100;
const int DOT_SIZE = 5;

int main(int argc, char* argv[]) {
    if (!InitSDL(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cerr << "Failed to initialize SDL" << std::endl;
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << std::endl;
        CleanupSDL();
        return 1;
    }

    SDL_Renderer* renderer = CreateRenderer();

    Maze* maze = new RectangularMaze(MAZE_WIDTH, MAZE_HEIGHT);
    SpanningtreeAlgorithm* algorithm = new BreadthFirstSearch;

    bool quit = false;
    while (!quit) {
        RunGame(renderer, maze, algorithm);

        // Display a prompt to quit or restart the game
        DrawText(renderer, "Press Q to quit, or any other key to restart", 0.25 * WINDOW_WIDTH, 0.58 * WINDOW_HEIGHT, { 255, 255, 255, 255 }, 14);
        SDL_RenderPresent(renderer);

        SDL_Event event;
        bool waitingForKey = true;
        while (waitingForKey) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_KEYDOWN) {
                    if (event.key.keysym.sym == SDLK_q) {
                        quit = true;
                        waitingForKey = false;
                    }
                    else {
                        waitingForKey = false;
                    }
                }
                else if (event.type == SDL_QUIT) {
                    quit = true;
                    waitingForKey = false;
                }
            }
        }
    }

    delete algorithm;
    delete maze;

    // Clean up SDL_ttf
    TTF_Quit();

    CleanupSDL();

    return 0;
}
