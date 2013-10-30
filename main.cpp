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

#if 1
        // Compute the average shortest path from vertex 0 to every other vertex
        double avgShortestPath = g.calcAvgShortestPath(0);

        std::cout << "For graph # " << i + 1 << ", the average shortest path from v0 = " << avgShortestPath << std::endl;
#else
        g.showEdgeListRepresentation();

        while (1)
        {
            unsigned int srcVertex, dstVertex;

            std::cout << "Enter source vertex index: ";
            std::cin >> srcVertex;
            std::cout << "Enter destination vertex index: ";
            std::cin >> dstVertex;

            std::vector<unsigned int> vShortestPathIndices;

            double shortestPath = g.calcShortestPath(srcVertex, dstVertex, vShortestPathIndices);

            if (shortestPath >= 0)
            {
                std::cout << "Shortest path from v" << srcVertex << " to v" << dstVertex << " is: ";

                for (std::vector<unsigned int>::const_reverse_iterator i = vShortestPathIndices.rbegin(); i != vShortestPathIndices.rend(); ++i)
                {
                    std::cout << "v" << *i << " -> ";
                }

                std::cout << std::endl << "cost = " << shortestPath << std::endl;
            }
            else
            {
                std::cout << "No path exists from v" << srcVertex << " to v" << dstVertex << "." << std::endl;
            }

            g.clearPathSpecificInfo();
            vShortestPathIndices.clear();
        }
#endif
    }

    // Return zero to the operating system to indicate successful program completion.
    return 0;
}

