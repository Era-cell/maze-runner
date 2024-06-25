#include "rectmaze.h"
#include <vector>
#include <tuple>
#include <random>
#include <chrono>

RectangularMaze::RectangularMaze(int width, int height)
    : Maze(width* height, 0, 0), width_(width), height_(height) {
    // Set start vertex (center of the maze)
    startvertex_ = VertexIndex(height_ / 2, width_ / 2);
}

int RectangularMaze::VertexIndex(int row, int column) {
    return row * width_ + column;
}

void RectangularMaze::GenerateRandomEndVertex() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> edge_distribution(0, 3);
    int edge = edge_distribution(generator);

    switch (edge) {
    case 0: { // Top edge
        std::uniform_int_distribution<int> distribution(0, width_ - 1);
        int column = distribution(generator);
        endvertex_ = VertexIndex(0, column);
        break;
    }
    case 1: { // Bottom edge
        std::uniform_int_distribution<int> distribution(0, width_ - 1);
        int column = distribution(generator);
        endvertex_ = VertexIndex(height_ - 1, column);
        break;
    }
    case 2: { // Left edge
        std::uniform_int_distribution<int> distribution(0, height_ - 1);
        int row = distribution(generator);
        endvertex_ = VertexIndex(row, 0);
        break;
    }
    case 3: { // Right edge
        std::uniform_int_distribution<int> distribution(0, height_ - 1);
        int row = distribution(generator);
        endvertex_ = VertexIndex(row, width_ - 1);
        break;
    }
    }
}

void RectangularMaze::InitialiseGraph() {
    Maze::InitialiseGraph();
    GenerateRandomEndVertex();  // Call the function to generate a new end vertex

    // Lower and upper boundaries
    for (int i = 0; i < width_; ++i) {
        if (VertexIndex(0, i) != endvertex_) {
            adjacencylist_[VertexIndex(0, i)].push_back(
                { -1, std::make_shared<LineBorder>(i, 0, i + 1, 0) });
        }
        if (VertexIndex(height_ - 1, i) != endvertex_) {
            adjacencylist_[VertexIndex(height_ - 1, i)].push_back(
                { -1, std::make_shared<LineBorder>(i, height_, i + 1, height_) });
        }
    }

    // Left and right boundaries, leaving space for entry and exit
    for (int i = 0; i < height_; ++i) {
        if (VertexIndex(i, 0) != endvertex_) {
            adjacencylist_[VertexIndex(i, 0)].push_back(
                { -1, std::make_shared<LineBorder>(0, i, 0, i + 1) });
        }
        if (VertexIndex(i, width_ - 1) != endvertex_) {
            adjacencylist_[VertexIndex(i, width_ - 1)].push_back(
                { -1, std::make_shared<LineBorder>(width_, i, width_, i + 1) });
        }
    }

    // Horizontally adjacent cells
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_ - 1; ++j) {
            std::shared_ptr<LineBorder> ptr =
                std::make_shared<LineBorder>(j + 1, i, j + 1, i + 1);
            adjacencylist_[VertexIndex(i, j)].push_back({ VertexIndex(i, j + 1), ptr });
            adjacencylist_[VertexIndex(i, j + 1)].push_back({ VertexIndex(i, j), ptr });
        }
    }

    // Vertically adjacent cells
    for (int i = 0; i < height_ - 1; ++i) {
        for (int j = 0; j < width_; ++j) {
            std::shared_ptr<LineBorder> ptr =
                std::make_shared<LineBorder>(j, i + 1, j + 1, i + 1);
            adjacencylist_[VertexIndex(i, j)].push_back({ VertexIndex(i + 1, j), ptr });
            adjacencylist_[VertexIndex(i + 1, j)].push_back({ VertexIndex(i, j), ptr });
        }
    }
}

std::tuple<double, double, double, double> RectangularMaze::GetCoordinateBounds() const {
    return std::make_tuple(0, 0, width_, height_);
}

std::pair<int, int> RectangularMaze::GetEndVertexCoordinates() const {
    int row = endvertex_ / width_;
    int column = endvertex_ % width_;
    return { row, column };
}
