#include <boost/random/uniform_int.hpp>
#include <boost/random/mersenne_twister.hpp>

#include "random.hpp"
#include "main.hpp"

boost::random::mt19937 rng;

void getRandomVertices(unsigned int numVertices, unsigned int& vertex1, unsigned int& vertex2)
{
    //boost::random::mt19937 rng;

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

void getRandomEdgeCost(double minEdgeCost, double maxEdgeCost, double& cost)
{
    //boost::random::mt19937 rng;

    boost::random::uniform_int_distribution<> dist(minEdgeCost, maxEdgeCost);

    cost = dist(rng);
}
