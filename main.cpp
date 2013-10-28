// Assuming:
//   - undirected graph with equal cost in both directions
//   - no self-loops
//   - non-negative costs

#include <iostream>

#include "graph.hpp"
#include "main.hpp"

int main()
{
    for (unsigned int i = 0; i < NUM_GRAPHS; ++i)
    {
        // Generate a random graph.
        Graph g(EDGE_DENSITY, MIN_EDGE_COST, MAX_EDGE_COST);

        // Compute the average shortest path from vertex 0 to every other vertex
        double avgShortestPath = g.calcAvgShortestPath(0);

        std::cout << "Graph # " << i + 1 << std::endl;

        g.showEdgeListRepresentation();

        std::cout << std::endl << std::endl;
    }

    // Return zero to the operating system to indicate successful program completion.
    return 0;
}

