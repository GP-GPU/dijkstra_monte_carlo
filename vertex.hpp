#pragma once

#include <vector>

class Vertex
{
private:
    std::vector<double> vEdgeCosts;
    double costOfPathFromSrcVertex;
    int indexOfPrevVertexOnPath;
    bool closed;

public:
    Vertex();

    double getEdgeCost(unsigned int) const;
    void setEdgeCost(unsigned int, double);
    void showEdgeCosts() const;
    bool edgeExists(unsigned int) const;

    double getCostOfPathFromSrcVertex() const;
    void setCostOfPathFromSrcVertex(double);

    int getIndexOfPrevVertexOnPath() const;
    void setIndexOfPrevVertexOnPath(int);

    void markClosed();
    bool isClosed() const;
};

class OpenSetVertex
{
private:
    unsigned int vertexIndex;
    double costOfPathFromSrcVertex;
    int indexOfPrevVertexOnPath;

public:
    OpenSetVertex(unsigned int, double, int);
    unsigned int getVertexIndex() const;
    double getCostOfPathFromSrcVertex() const;
    int getIndexOfPrevVertexOnPath() const;
};

class OpenSetVertexCompare
{
public:
    bool operator()(const OpenSetVertex& lhs, const OpenSetVertex& rhs) const;
};
