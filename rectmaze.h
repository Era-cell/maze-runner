#pragma once
#ifndef MAZE_H
#define MAZE_H

#ifndef M_PI
#define M_PI 3.1415926
#endif

#include "cellborder.h"
#include "spanningtreealgo.h"
#include <memory>
#include <vector>
#include <string> // For std::string and std::tuple

class Maze {
public:
    Maze(int = 0, int = 0, int = 1);
    void GenerateMaze(SpanningtreeAlgorithm*);
    void PrintMazeSVG(const std::string&, bool = false) const;
    virtual void InitialiseGraph() = 0;
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> GetLines() const; // Updated line

protected:
    // Solving a maze is equivalent to finding a path in a graph
    int vertices_;
    Graph adjacencylist_, solution_;
    int startvertex_, endvertex_;

    void RemoveBorders(const std::vector<std::pair<int, int>>&);
    virtual std::tuple<double, double, double, double> GetCoordinateBounds() const = 0;
};

#endif /* end of include guard: MAZE_H */

#ifndef RECTMAZE_H
#define RECTMAZE_H

#include "maze.h"

class RectangularMaze : public Maze {
public:
    RectangularMaze(int width, int height);
    void InitialiseGraph() override;
    std::pair<int, int> GetEndVertexCoordinates() const;

private:
    int width_, height_;

    int VertexIndex(int row, int column);
    std::tuple<double, double, double, double> GetCoordinateBounds() const override;
    void GenerateRandomEndVertex(); // Add this declaration
};

#endif /* end of include guard: RECTMAZE_H */
