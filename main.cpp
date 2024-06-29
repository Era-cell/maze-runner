#include "renderer.h"
#include "sdl_utils.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "rectmaze.h"
#include <iostream>
#include "game.h"
#include "globals.h"

int main(int argc, char* argv[]) {
    if (!InitSDL(WINDOW_WIDTH, WINDOW_HEIGHT)) {
        std::cout << WINDOW_WIDTH << WINDOW_HEIGHT;
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
        DrawText(renderer, "Press Q to quit, or any other key to restart", 0.25 * WINDOW_WIDTH, 0.58 * WINDOW_HEIGHT, { 255, 255, 255, 255 }, 24);
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
