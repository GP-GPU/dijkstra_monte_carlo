#pragma once

#include <vector>
#include <queue>

#include "vertex.hpp"

class Graph
{
private:
    std::vector<Vertex> vVertices;

public:
    Graph(double, double, double);
    double calcShortestPath(unsigned int, unsigned int, std::vector<unsigned int>&);
    double calcAvgShortestPath(unsigned int);
    void showEdgeListRepresentation() const;
    void updateOpenSet(std::priority_queue<OpenSetVertex, std::vector<OpenSetVertex>, OpenSetVertexCompare>&, unsigned int);
};
