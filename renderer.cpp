#include "renderer.h"
#include "sdl_utils.h"
#include <SDL_ttf.h>
#include <iostream>
#include "globals.h"
const char* FONT_PATH = "G:/CppDev/SDL2_ttf/font/november.ttf";

// Function to render text using SDL_ttf
void DrawText(SDL_Renderer* renderer, const std::string& text, int x, int y, SDL_Color color, int fontSize) {
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

void DrawScoreboard(SDL_Renderer* renderer, int wins, int streak, int maxStreak) {
    SDL_Color textColor = { 255, 255, 255, 255 }; // White color for text

    int fontSize = 18; // Increased font size

    // Render wins text
    std::string winsText = "Wins: " + std::to_string(wins);
    DrawText(renderer, winsText, 20, 20, textColor, fontSize + 1);

    // Determine streak text and color
    std::string streakText;
    SDL_Color streakColor;

    if (streak >= 0) {
        streakText = "Win Streak: " + std::to_string(streak);
        streakColor = { 0, 255, 0, 255 }; // Green color for win streak
    }
    else {
        streakText = "Lose Streak: " + std::to_string(-streak);
        streakColor = { 255, 0, 0, 255 }; // Red color for lose streak
    }

    // Render streak text
    DrawText(renderer, streakText, 20, 50, streakColor, fontSize + 1);

    // Render max streak text
    SDL_Color maxStreakColor = { 255, 165, 0, 255 }; // Orange color for max streak
    std::string maxStreakText = "Max Streak: " + std::to_string(maxStreak);
    int maxStreakX = WINDOW_HEIGHT - 200; // Adjust x position to fit the text within the window
    int maxStreakY = 20;

    DrawText(renderer, maxStreakText, maxStreakX, maxStreakY, maxStreakColor, fontSize + 2);

    // Render instructions at the bottom left
    std::string instructions1 = "Use arrows to navigate";
    std::string instructions2 = "Reach the exit to win";
    std::string instructions3 = "Hold SHIFT for movement boost";
    int instructionX = 10;
    int instructionY = WINDOW_HEIGHT - 200; // Adjust y position to fit the instructions within the window
    int instructionSpacing = 30; // Space between each line of instruction

    DrawText(renderer, instructions1, instructionX, instructionY, textColor, fontSize);
    DrawText(renderer, instructions2, instructionX, instructionY + instructionSpacing, textColor, fontSize);
    DrawText(renderer, instructions3, instructionX, instructionY + 2 * instructionSpacing, textColor, fontSize);
}


void DrawMaze(SDL_Renderer* renderer, const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& lines, const SDL_Rect& redDot, int scale, int shift, int wins, int streak, int maxStreak) {
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

    DrawScoreboard(renderer, wins, streak, maxStreak); // Draw scoreboard and instructions

    // Draw game title at the bottom right
    SDL_Color greyColor = { 169, 169, 169, 255 }; // Grey color for text
    std::string gameTitle = "Maze Runner";
    int textWidth = 150; // Approximate width of the text
    int textHeight = 20; // Approximate height of the text
    int titleX = WINDOW_WIDTH - textWidth - 200; // 10 pixels from the right edge
    int titleY = WINDOW_HEIGHT - textHeight - 150; // 10 pixels from the bottom edge
    DrawText(renderer, gameTitle, titleX, titleY, greyColor, 40);

    SDL_RenderPresent(renderer); // Present the rendered frame
}
