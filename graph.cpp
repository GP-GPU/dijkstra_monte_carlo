#include <vector>
#include <iostream>

#include "graph.hpp"
#include "random.hpp"
#include "main.hpp"

unsigned int calcNumEdges(double edgeDensity)
{
    // For a graph of N vertices, the maximum number of edges (i.e. for a complete graph)
    //     without self loops = (N * (N-1))/2
    //     with self loops    = ((N * (N-1))/2) + N
    unsigned int maxNumEdges = ((NUM_VERTICES_IN_GRAPH * (NUM_VERTICES_IN_GRAPH - 1)) / 2);

    if (SELF_LOOPS_ALLOWED == true)
    {
        maxNumEdges += NUM_VERTICES_IN_GRAPH;
    }

    return (maxNumEdges * edgeDensity);
}

double calcVectorAvg(const std::vector<double>& v)
{
    double sum = 0;

    for (std::vector<double>::const_iterator i = v.begin(); i != v.end(); ++i)
    {
        sum += *i;
    }

    return (sum / v.size());
}

Graph::Graph(double edgeDensity, double minEdgeCost, double maxEdgeCost) : vVertices(NUM_VERTICES_IN_GRAPH)
{
    // The edge density must be between 0 & 1. Set it to a default of 0.5 if an incorrect value is
    // given.
    if ((edgeDensity < 0) || (edgeDensity > 1))
    {
        std::cout << "Invalid edge density specified, setting it to default of 0.5" << std::endl;
        edgeDensity = 0.5;
    }

    // Get the actual number of edges from the edge density
    unsigned int numEdges = calcNumEdges(edgeDensity);

    // Randomly generate the edges
    for (unsigned int i = 0; i < numEdges; ++i)
    {
        unsigned int vertex1, vertex2;
        double weight;

        getRandomVertices(NUM_VERTICES_IN_GRAPH, vertex1, vertex2);
//std::cout << "got random vertices - v" << vertex1 << " & v" << vertex2 << std::endl;

        while (vVertices[vertex1].edgeAlreadyExists(vertex2))
        {
//std::cout << "edge v" << vertex1 << "-->v" << vertex2 << " already exists :(" << std::endl;
            getRandomVertices(NUM_VERTICES_IN_GRAPH, vertex1, vertex2);
//std::cout << "got new random vertices - v" << vertex1 << " & v" << vertex2 << std::endl;
        }

        getRandomEdgeWeight(minEdgeCost, maxEdgeCost, weight);
//std::cout << "got random edge weight " << weight << std::endl;

        // Set the edge costs vectors in the two vertices appropriately.
        vVertices[vertex1].setEdgeCost(vertex2, weight);
        vVertices[vertex2].setEdgeCost(vertex1, weight);
    }
}

double Graph::calcShortestPath(unsigned int srcVertexIndex, unsigned int dstVertexIndex) const
{
}

double Graph::calcAvgShortestPath(unsigned int srcVertexIndex) const
{
    std::vector<double> shortestPathsVector;

    for (unsigned int i = 0; i < NUM_VERTICES_IN_GRAPH; ++i)
    {
        // Don't bother calculating the shortest path from the source vertex to itself.
        if (i == srcVertexIndex)
        {
            continue;
        }

        double shortestPath = calcShortestPath(srcVertexIndex, i);

        // Add to the shortest paths vector only if a path actually exists.
        if (shortestPath >= 0)
        {
            shortestPathsVector.push_back(shortestPath);
        }
    }

    return (calcVectorAvg(shortestPathsVector));
}

void Graph::showEdgeListRepresentation() const
{
    unsigned int vertexIndex = 0;

    for (std::vector<Vertex>::const_iterator i = vVertices.begin(); i != vVertices.end(); ++i)
    {
        std::cout << "v" << vertexIndex << " : ";

        i->showEdgeCosts();

        ++vertexIndex;

        std::cout << std::endl;
    }
}
