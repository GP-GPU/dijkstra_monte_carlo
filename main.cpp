// Assuming:
//   - undirected graph with equal cost in both directions
//   - non-negative costs

#include <iostream>

#include "graph.hpp"
#include "main.hpp"

// Function to return the average of all values in a vector of doubles
double calcVectorAvg(const std::vector<double>& v)
{
    double sum = 0;

    for (std::vector<double>::const_iterator i = v.begin(); i != v.end(); ++i)
    {
        sum += *i;
    }

    return (sum / v.size());
}

// The main function
int main()
{
    std::cout << "Program parameters:" << std::endl;
    std::cout << "    number of graphs used in the simulation = " << NUM_GRAPHS << std::endl;
    std::cout << "    number of vertices in each graph = " << NUM_VERTICES_IN_GRAPH << std::endl;
    std::cout << "    self loops allowed = " << ((SELF_LOOPS_ALLOWED) ? "Yes" : "No") << std::endl;
    std::cout << "    edge density = " << EDGE_DENSITY << " (" << (EDGE_DENSITY * 100) << "%)" << std::endl;
    std::cout << "    minimum edge cost = " << MIN_EDGE_COST << std::endl;
    std::cout << "    maximum edge cost = " << MAX_EDGE_COST << std::endl;
    std::cout << std::endl;

    std::vector<double> avgShortestPaths;

    for (unsigned int i = 0; i < NUM_GRAPHS; ++i)
    {
        // Generate a random graph.
        Graph g(EDGE_DENSITY, MIN_EDGE_COST, MAX_EDGE_COST);

#if 1
        unsigned int srcVertexIndex = 0;

        // Compute the average shortest path from the source vertex to every other vertex.
        double avgShortestPath = g.calcAvgShortestPath(srcVertexIndex);

        if (SHOW_AVG_SHORTEST_PATH_PER_GRAPH)
        {
            std::cout << "For graph # " << i + 1 << ", the average shortest path from v" << srcVertexIndex << " = " << avgShortestPath << std::endl;
        }

        avgShortestPaths.push_back(avgShortestPath);
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

    std::cout << std::endl << "The average of the average shortest paths calculated for all " << NUM_GRAPHS << " graphs is " << calcVectorAvg(avgShortestPaths) << std::endl;

    // Return zero to the operating system to indicate successful program completion.
    return 0;
}

