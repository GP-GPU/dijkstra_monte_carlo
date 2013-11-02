#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "random.hpp"
#include "main.hpp"

// Global seed set to the same value every time the program executes. Should be randomised for
// better random number generation.
boost::random::mt19937 rng;

// Function to get two random vertices. The two vertices may be same only if the graph can have
// self loops.
void getRandomVertices(unsigned int numVertices, unsigned int& vertex1, unsigned int& vertex2)
{
    boost::random::uniform_int_distribution<> dist(0, (numVertices - 1));

    vertex1 = dist(rng);

    vertex2 = dist(rng);

    if (SELF_LOOPS_ALLOWED == false)
    {
        while (vertex1 == vertex2)
        {
            vertex2 = dist(rng);
        }
    }
}

// Function to generate a random edge cost within the given bounds.
void getRandomEdgeCost(double minEdgeCost, double maxEdgeCost, double& cost)
{
    boost::random::uniform_int_distribution<> dist(minEdgeCost, maxEdgeCost);

    cost = dist(rng);
}
