#pragma once

#include <vector>

#include "vertex.hpp"

class Graph
{
private:
    std::vector<Vertex> vVertices;

public:
    Graph(double, double, double);
    double calcShortestPath(unsigned int, unsigned int) const;
    double calcAvgShortestPath(unsigned int) const;
    void showEdgeListRepresentation() const;
};
