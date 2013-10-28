#include <vector>
#include <iostream>

#include "vertex.hpp"
#include "main.hpp"

Vertex::Vertex() : vEdgeCosts(NUM_VERTICES_IN_GRAPH, -1)
{
}

void Vertex::setEdgeCost(unsigned int remoteVertex, double weight)
{
    vEdgeCosts[remoteVertex] = weight;
}

void Vertex::showEdgeCosts() const
{
    unsigned int remoteVertexIndex = 0;

    for (std::vector<int>::const_iterator i = vEdgeCosts.begin(); i != vEdgeCosts.end(); ++i)
    {
        if (*i >= 0)
        {
            std::cout << "v" << remoteVertexIndex << "(" << *i << "), ";
        }

        ++remoteVertexIndex;
    }
}

bool Vertex::edgeAlreadyExists(unsigned int remoteVertex) const
{
    return (vEdgeCosts[remoteVertex] >= 0);
}
