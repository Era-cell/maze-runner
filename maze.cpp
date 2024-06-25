#include "maze.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>

Maze::Maze(int vertices, int startvertex, int endvertex)
    : vertices_(vertices), startvertex_(startvertex), endvertex_(endvertex) {}

void Maze::InitialiseGraph() {
    adjacencylist_.clear();
    adjacencylist_.resize(vertices_);
}

void Maze::GenerateMaze(SpanningtreeAlgorithm* algorithm) {
    auto spanningtree = algorithm->SpanningTree(vertices_, adjacencylist_);
    RemoveBorders(spanningtree);
}

void Maze::RemoveBorders(const std::vector<std::pair<int, int>>& edges) {
    for (const auto& [u, v] : edges) {
        adjacencylist_[u].erase(
            std::find_if(adjacencylist_[u].begin(), adjacencylist_[u].end(),
                [v = v](const Edge& e) { return std::get<0>(e) == v; }));
        adjacencylist_[v].erase(
            std::find_if(adjacencylist_[v].begin(), adjacencylist_[v].end(),
                [u = u](const Edge& e) { return std::get<0>(e) == u; }));
    }
}

void Maze::PrintMazeSVG(const std::string& outputprefix, bool solution) const {
    std::ofstream svgfile(outputprefix + ".svg");
    if (!svgfile) {
        std::cerr << "Error opening " << outputprefix << ".svg for writing.\n";
        std::cerr << "Terminating.";
        exit(1);
    }
    double xmin, ymin, xmax, ymax;
    std::tie(xmin, ymin, xmax, ymax) = GetCoordinateBounds();
    int xresolution = (xmax - xmin + 2) * 30,
        yresolution = (ymax - ymin + 2) * 30;

    svgfile << "<svg width=\"" << xresolution << "\" height=\"" << yresolution
        << "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
    svgfile << "<g transform=\"translate(" << (1 - xmin) * 30 << ","
        << yresolution - (1 - ymin) * 30 << ") scale(1,-1)\">" << std::endl;
    svgfile << "<rect x=\"" << (xmin - 1) * 30 << "\" y=\"" << (ymin - 1) * 30
        << "\" width=\"" << xresolution << "\" height=\"" << yresolution
        << "\" fill=\"white\"/>" << std::endl;

    for (int i = 0; i < vertices_; ++i) {
        for (const auto& edge : adjacencylist_[i]) {
            if (std::get<0>(edge) < i) {
                svgfile << std::get<1>(edge)->SVGPrintString("black") << "\n";
            }
        }
    }
    svgfile << "</g>" << std::endl;
    svgfile << "</svg>" << std::endl;
}

std::vector<std::tuple<std::string, std::string, std::string, std::string>> Maze::GetLines() const {
    std::vector<std::tuple<std::string, std::string, std::string, std::string>> lines;
    for (int i = 0; i < vertices_; ++i) {
        for (const auto& edge : adjacencylist_[i]) {
            if (std::get<0>(edge) < i) {
                auto border = dynamic_cast<LineBorder*>(std::get<1>(edge).get());
                if (border) {
                    lines.emplace_back(std::to_string(border->x1_), std::to_string(border->y1_),
                        std::to_string(border->x2_), std::to_string(border->y2_));
                }
            }
        }
    }
    return lines;
}
