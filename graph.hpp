#pragma once

#include <vector>

#include "vertex.hpp"
#include "priority_queue.hpp"

class Graph
{
private:
    std::vector<Vertex> vVertices;

public:
    Graph(double, double, double);
    double calcShortestPath(unsigned int, unsigned int, std::vector<unsigned int>&);
    double calcAvgShortestPath(unsigned int);
    void showEdgeListRepresentation() const;
    void updateOpenSet(PriorityQueue<OpenSetVertex, OpenSetVertexCompareCost, OpenSetVertexCompareIndex>&, unsigned int);
    void clearPathSpecificInfo();
};
