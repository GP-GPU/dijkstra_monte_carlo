#include <vector>
#include <iostream>
#include <limits>

#include "vertex.hpp"
#include "main.hpp"

// Constructor for the Vertex class. Initialises a vertex object to it's default state.
Vertex::Vertex() : vEdgeCosts(NUM_VERTICES_IN_GRAPH, -1),
                   costOfPathFromSrcVertex(std::numeric_limits<double>::max()),
                   indexOfPrevVertexOnPath(-1),
                   closed(false)
{
}

// Function to get the edge cost to the given remote vertex.
double Vertex::getEdgeCost(unsigned int remoteVertex) const
{
    return vEdgeCosts[remoteVertex];
}

// Function to set the edge cost to the given remote vertex.
void Vertex::setEdgeCost(unsigned int remoteVertex, double weight)
{
    vEdgeCosts[remoteVertex] = weight;
}

// Function to show the connected vertices along with their associated costs.
void Vertex::showEdgeCosts() const
{
    unsigned int remoteVertexIndex = 0;

    for (std::vector<double>::const_iterator i = vEdgeCosts.begin(); i != vEdgeCosts.end(); ++i)
    {
        if (*i >= 0)
        {
            std::cout << "v" << remoteVertexIndex << "(" << *i << "), ";
        }

        ++remoteVertexIndex;
    }
}

// Function to check whether an edge exists or not to the given remote vertex.
bool Vertex::edgeExists(unsigned int remoteVertex) const
{
    return (vEdgeCosts[remoteVertex] >= 0);
}

// Function to get the total cost from the source vertex.
double Vertex::getCostOfPathFromSrcVertex() const
{
    return costOfPathFromSrcVertex;
}

// Function to set the total cost from the source vertex.
void Vertex::setCostOfPathFromSrcVertex(double cost)
{
    costOfPathFromSrcVertex = cost;
}

// Function to get the index of the previous vertex on the current shortest path to the source
// vertex.
int Vertex::getIndexOfPrevVertexOnPath() const
{
    return indexOfPrevVertexOnPath;
}

// Function to set the index of the previous vertex on the current shortest path to the source
// vertex.
void Vertex::setIndexOfPrevVertexOnPath(int index)
{
    indexOfPrevVertexOnPath = index;
}

// Function to mark the current vertex closed (implies that the shortest path to the source vertex
// has been finalised).
void Vertex::markClosed()
{
    closed = true;
}

// Function to check whether the vertex is closed or not.
bool Vertex::isClosed() const
{
    return closed;
}

// Function to reset all path specific information stored in a Vertex object. Needed for any new
// path calculation.
void Vertex::clearPathSpecificInfo()
{
    costOfPathFromSrcVertex = std::numeric_limits<double>::max();
    indexOfPrevVertexOnPath = -1;
    closed = false;
}

// Counstructor for the OpenSetVertex class. Sets the object to it's default state.
OpenSetVertex::OpenSetVertex(unsigned int vI, double c, int pVI) : vertexIndex(vI),
                                                                   costOfPathFromSrcVertex(c),
                                                                   indexOfPrevVertexOnPath(pVI)
{
}

// Function to get the index of a vertex in the open set.
unsigned int OpenSetVertex::getVertexIndex() const
{
    return vertexIndex;
}

// Function to get the total cost from the source vertex for a vertex in the open set.
double OpenSetVertex::getCostOfPathFromSrcVertex() const
{
    return costOfPathFromSrcVertex;
}

// Function to set the total cost from the source vertex for a vertex in the open set.
void OpenSetVertex::setCostOfPathFromSrcVertex(double cost)
{
    costOfPathFromSrcVertex = cost;
}

// Function to get the index of the previous vertex on the current shortest path to the source
// vertex for a vertex in the open set.
int OpenSetVertex::getIndexOfPrevVertexOnPath() const
{
    return indexOfPrevVertexOnPath;
}

// Function to set the index of the previous vertex on the current shortest path to the source
// vertex for a vertex in the open set.
void OpenSetVertex::setIndexOfPrevVertexOnPath(int index)
{
    indexOfPrevVertexOnPath = index;
}

bool OpenSetVertexCompareIndex::operator()(const OpenSetVertex& lhs, const OpenSetVertex& rhs) const
{
    return (lhs.getVertexIndex() == rhs.getVertexIndex());
}

bool OpenSetVertexCompareCost::operator()(const OpenSetVertex& lhs, const OpenSetVertex& rhs) const
{
    return (lhs.getCostOfPathFromSrcVertex() < rhs.getCostOfPathFromSrcVertex());
}
