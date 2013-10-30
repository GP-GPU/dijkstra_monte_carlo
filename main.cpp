// Assuming:
//   - undirected graph with equal cost in both directions
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

        std::cout << "For graph # " << i + 1 << ", the average shortest path from v0 = " << avgShortestPath << std::endl;

        //g.showEdgeListRepresentation();

        std::cout << std::endl;
    }

    // Return zero to the operating system to indicate successful program completion.
    return 0;
}

