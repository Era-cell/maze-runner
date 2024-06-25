#include "renderer.h"
#include "sdl_utils.h"
#include <SDL_ttf.h>
#include <iostream>

const char* FONT_PATH = "G:/CppDev/SDL2_ttf/font/pacifico.ttf";

// Function to render text using SDL_ttf
void DrawText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, int fontSize) {

    fontSize += 10;
    // Load a font
    TTF_Font* font = TTF_OpenFont(FONT_PATH, fontSize);
    if (!font) {
        std::cerr << "Failed to load font '" << FONT_PATH << "': " << TTF_GetError() << std::endl;
        return;
    }

    // Render text onto a surface
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        return;
    }

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        TTF_CloseFont(font);
        return;
    }

    // Set rendering area and render to screen
    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    // Clean up resources
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
}


void DrawScoreboard(SDL_Renderer* renderer, int wins, int streak) {
    SDL_Color textColor = { 255, 255, 255, 255 }; // White color for text

    // Render wins text
    std::string winsText = "Wins: " + std::to_string(wins);
    DrawText(renderer, winsText, 10, 10, textColor, 14);

    // Render streak text
    std::string streakText = "Streak: " + std::to_string(streak);
    DrawText(renderer, streakText, 10, 40, textColor, 14);
}


void DrawMaze(SDL_Renderer* renderer, const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& lines, const SDL_Rect& redDot, int scale, int shift, int wins, int streak) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Clear with black color
    SDL_RenderClear(renderer); // Clear the entire renderer

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set drawing color to white

    for (const auto& line : lines) {
        int x1 = static_cast<int>(std::stod(std::get<0>(line)) * scale) + shift;
        int y1 = static_cast<int>(std::stod(std::get<1>(line)) * scale) + shift;
        int x2 = static_cast<int>(std::stod(std::get<2>(line)) * scale) + shift;
        int y2 = static_cast<int>(std::stod(std::get<3>(line)) * scale) + shift;

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2); // Draw each line
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Set drawing color to red
    SDL_RenderFillRect(renderer, &redDot); // Draw the red dot

    DrawScoreboard(renderer, wins, streak); // Draw scoreboard

    SDL_RenderPresent(renderer); // Present the rendered frame
}
