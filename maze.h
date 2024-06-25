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
    virtual ~Maze() = default; // Add virtual destructor
    void GenerateMaze(SpanningtreeAlgorithm*);
    void PrintMazeSVG(const std::string&, bool = false) const;
    virtual void InitialiseGraph() = 0;
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> GetLines() const; // Updated line
    virtual std::tuple<double, double, double, double> GetCoordinateBounds() const = 0;

protected:
    // Solving a maze is equivalent to finding a path in a graph
    int vertices_;
    Graph adjacencylist_, solution_;
    int startvertex_, endvertex_;

    void RemoveBorders(const std::vector<std::pair<int, int>>&);
};

#endif /* end of include guard: MAZE_H */
