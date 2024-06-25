#include "maze_handler.h"

void RemoveCubeEdges(SDL_Rect& redDot, std::vector<std::tuple<std::string, std::string, std::string, std::string>>& lines, int mazeWidth, int mazeHeight, int shift, int scale) {
    int cubeX = (redDot.x - shift) / scale;
    int cubeY = (redDot.y - shift) / scale;

    auto it = lines.begin();
    while (it != lines.end()) {
        int x1 = static_cast<int>(std::stod(std::get<0>(*it)));
        int y1 = static_cast<int>(std::stod(std::get<1>(*it)));
        int x2 = static_cast<int>(std::stod(std::get<2>(*it)));
        int y2 = static_cast<int>(std::stod(std::get<3>(*it)));

        bool removeLine = false;

        if ((x1 == cubeX && y1 == cubeY && x2 == cubeX + 1 && y2 == cubeY) ||
            (x1 == cubeX && y1 == cubeY && x2 == cubeX && y2 == cubeY + 1) ||
            (x1 == cubeX + 1 && y1 == cubeY && x2 == cubeX + 1 && y2 == cubeY + 1) ||
            (x1 == cubeX && y1 == cubeY + 1 && x2 == cubeX + 1 && y2 == cubeY + 1)) {

            if (cubeX == 0 && x1 == cubeX && x2 == cubeX) {
                removeLine = false;
            }
            else if (cubeX == mazeWidth - 1 && x1 == cubeX + 1 && x2 == cubeX + 1) {
                removeLine = false;
            }
            else if (cubeY == 0 && y1 == cubeY && y2 == cubeY) {
                removeLine = false;
            }
            else if (cubeY == mazeHeight - 1 && y1 == cubeY + 1 && y2 == cubeY + 1) {
                removeLine = false;
            }
            else {
                removeLine = true;
            }
        }

        if (removeLine) {
            it = lines.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool IsCollision(SDL_Rect redDot, const std::vector<std::tuple<std::string, std::string, std::string, std::string>>& lines, int shift, int scale) {
    SDL_Rect boundingBox = { redDot.x - 1, redDot.y - 1, redDot.w + 2, redDot.h + 2 };

    for (const auto& line : lines) {
        int x1 = static_cast<int>(std::stod(std::get<0>(line)) * scale) + shift;
        int y1 = static_cast<int>(std::stod(std::get<1>(line)) * scale) + shift;
        int x2 = static_cast<int>(std::stod(std::get<2>(line)) * scale) + shift;
        int y2 = static_cast<int>(std::stod(std::get<3>(line)) * scale) + shift;

        if (SDL_IntersectRectAndLine(&boundingBox, &x1, &y1, &x2, &y2)) {
            return true;
        }
    }
    return false;
}

bool IsExitReached(SDL_Rect redDot, int mazeWidth, int mazeHeight, int shift, int scale) {
    // Calculate the maze boundaries including the shift and scale
    int mazeLeftBoundary = shift;
    int mazeRightBoundary = shift + mazeWidth * scale - 1;
    int mazeTopBoundary = shift;
    int mazeBottomBoundary = shift + mazeHeight * scale - 1;

    // Check if red dot's screen coordinates exceed the maze boundaries
    if (redDot.x < mazeLeftBoundary || redDot.x > mazeRightBoundary ||
        redDot.y < mazeTopBoundary || redDot.y > mazeBottomBoundary) {
        return true;
    }
    return false;
}
