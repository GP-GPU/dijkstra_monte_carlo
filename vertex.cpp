#include <vector>
#include <iostream>

#include "vertex.hpp"
#include "main.hpp"

Vertex::Vertex() : vEdgeCosts(NUM_VERTICES_IN_GRAPH, -1),
                   costOfPathFromSrcVertex(65535),
                   indexOfPrevVertexOnPath(-1),
                   closed(false)
{
}

double Vertex::getEdgeCost(unsigned int remoteVertex) const
{
    return vEdgeCosts[remoteVertex];
}

void Vertex::setEdgeCost(unsigned int remoteVertex, double weight)
{
    vEdgeCosts[remoteVertex] = weight;
}

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

bool Vertex::edgeExists(unsigned int remoteVertex) const
{
    return (vEdgeCosts[remoteVertex] >= 0);
}

double Vertex::getCostOfPathFromSrcVertex() const
{
    return costOfPathFromSrcVertex;
}

void Vertex::setCostOfPathFromSrcVertex(double cost)
{
    costOfPathFromSrcVertex = cost;
}

int Vertex::getIndexOfPrevVertexOnPath() const
{
    return indexOfPrevVertexOnPath;
}

void Vertex::setIndexOfPrevVertexOnPath(int index)
{
    indexOfPrevVertexOnPath = index;
}

void Vertex::markClosed()
{
    closed = true;
}

bool Vertex::isClosed() const
{
    return closed;
}

OpenSetVertex::OpenSetVertex(unsigned int vI, double c, int pVI) : vertexIndex(vI),
                                                                   costOfPathFromSrcVertex(c),
                                                                   indexOfPrevVertexOnPath(pVI)
{
}

unsigned int OpenSetVertex::getVertexIndex() const
{
    return vertexIndex;
}

double OpenSetVertex::getCostOfPathFromSrcVertex() const
{
    return costOfPathFromSrcVertex;
}

void OpenSetVertex::setCostOfPathFromSrcVertex(double cost)
{
    costOfPathFromSrcVertex = cost;
}

int OpenSetVertex::getIndexOfPrevVertexOnPath() const
{
    return indexOfPrevVertexOnPath;
}

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
