#include <vector>
#include <iostream>

#include "graph.hpp"
#include "random.hpp"
#include "main.hpp"
#include "priority_queue.hpp"

unsigned int calcNumEdges(double edgeDensity)
{
    // For a graph of N vertices, the maximum number of edges (i.e. for a complete graph)
    //     without self loops = (N * (N-1))/2
    //     with self loops    = ((N * (N-1))/2) + N
    unsigned int maxNumEdges = ((NUM_VERTICES_IN_GRAPH * (NUM_VERTICES_IN_GRAPH - 1)) / 2);

    if (SELF_LOOPS_ALLOWED == true)
    {
        maxNumEdges += NUM_VERTICES_IN_GRAPH;
    }

    return (maxNumEdges * edgeDensity);
}

double calcVectorAvg(const std::vector<double>& v)
{
    double sum = 0;

    for (std::vector<double>::const_iterator i = v.begin(); i != v.end(); ++i)
    {
        sum += *i;
    }

    return (sum / v.size());
}

void Graph::updateOpenSet(PriorityQueue<OpenSetVertex, OpenSetVertexCompareCost, OpenSetVertexCompareIndex>& openSet, unsigned int newestClosedVertexIndex)
{
    Vertex v = vVertices[newestClosedVertexIndex];

    for (unsigned int i = 0; i < NUM_VERTICES_IN_GRAPH; ++i)
    {
        if (vVertices[i].isClosed())
        {
            continue;
        }

        if (v.edgeExists(i))
        {
            double costOfPathViaV = v.getCostOfPathFromSrcVertex() + v.getEdgeCost(i);

            if (costOfPathViaV < vVertices[i].getCostOfPathFromSrcVertex())
            {
                vVertices[i].setCostOfPathFromSrcVertex(costOfPathViaV);
                vVertices[i].setIndexOfPrevVertexOnPath(newestClosedVertexIndex);

                openSet.updateIfExistsElseAdd(OpenSetVertex(i, costOfPathViaV, newestClosedVertexIndex));
            }
        }
    }
}

Graph::Graph(double edgeDensity, double minEdgeCost, double maxEdgeCost) : vVertices(NUM_VERTICES_IN_GRAPH)
{
    // The edge density must be between 0 & 1. Set it to a default of 0.5 if an incorrect value is
    // given.
    if ((edgeDensity < 0) || (edgeDensity > 1))
    {
        std::cout << "Invalid edge density specified, setting it to default of 0.5" << std::endl;
        edgeDensity = 0.5;
    }

    // Get the actual number of edges from the edge density
    unsigned int numEdges = calcNumEdges(edgeDensity);

    // Randomly generate the edges
    for (unsigned int i = 0; i < numEdges; ++i)
    {
        unsigned int vertex1, vertex2;
        double weight;

        getRandomVertices(NUM_VERTICES_IN_GRAPH, vertex1, vertex2);
//std::cout << "got random vertices - v" << vertex1 << " & v" << vertex2 << std::endl;

        while (vVertices[vertex1].edgeExists(vertex2))
        {
//std::cout << "edge v" << vertex1 << "-->v" << vertex2 << " already exists :(" << std::endl;
            getRandomVertices(NUM_VERTICES_IN_GRAPH, vertex1, vertex2);
//std::cout << "got new random vertices - v" << vertex1 << " & v" << vertex2 << std::endl;
        }

        getRandomEdgeWeight(minEdgeCost, maxEdgeCost, weight);
//std::cout << "got random edge weight " << weight << std::endl;

        // Set the edge costs vectors in the two vertices appropriately.
        vVertices[vertex1].setEdgeCost(vertex2, weight);
        vVertices[vertex2].setEdgeCost(vertex1, weight);
    }
}

double Graph::calcShortestPath(unsigned int srcVertexIndex, unsigned int dstVertexIndex, std::vector<unsigned int>& vShortestPath)
{
    unsigned int numClosedVertices = 0;

    // The 'openSet' priority queue contains vertices currently under consideration for being
    // added to the closed set.
    PriorityQueue<OpenSetVertex, OpenSetVertexCompareCost, OpenSetVertexCompareIndex> openSet;

    // The source vertex can be added to the closed set immediately with zero cost and no previous
    // vertex.
    vVertices[srcVertexIndex].setCostOfPathFromSrcVertex(0);
    vVertices[srcVertexIndex].setIndexOfPrevVertexOnPath(-1);
    vVertices[srcVertexIndex].markClosed();
    vShortestPath.push_back(srcVertexIndex);
    ++numClosedVertices;

    unsigned int newestClosedVertexIndex = srcVertexIndex;

    while (numClosedVertices != NUM_VERTICES_IN_GRAPH)
    {
        // Break out if the destination vertex has been reached.
        if (newestClosedVertexIndex == dstVertexIndex)
        {
            break;
        }

        // Update the open set with vertices that can be reached from the vertex most recently
        // added to the closed set (provided that these vertices are not already in the closed
        // or open sets).
        updateOpenSet(openSet, newestClosedVertexIndex);

        // Select the vertex in the open set that has the lowest cost from the source vertex.
        OpenSetVertex tmp = openSet.top();
        newestClosedVertexIndex = tmp.getVertexIndex();
        openSet.pop();

        // Add this vertex to the closed set.
        vVertices[newestClosedVertexIndex].setCostOfPathFromSrcVertex(tmp.getCostOfPathFromSrcVertex());
        vVertices[newestClosedVertexIndex].setIndexOfPrevVertexOnPath(tmp.getIndexOfPrevVertexOnPath());
        vVertices[newestClosedVertexIndex].markClosed();
        vShortestPath.push_back(newestClosedVertexIndex);
        ++numClosedVertices;
    }

    return (vVertices[dstVertexIndex].getCostOfPathFromSrcVertex());
}

double Graph::calcAvgShortestPath(unsigned int srcVertexIndex)
{
    // Vector containing the shortest path costs from the source vertex to every other vertex.
    // Costs are added to this vector only if a path actually exists from the source vertex to the
    // vertex under consideration.
    // This function can then return the average of the values in this vector.
    std::vector<double> vshortestPathValues(NUM_VERTICES_IN_GRAPH, 0);

    for (unsigned int i = 0; i < NUM_VERTICES_IN_GRAPH; ++i)
    {
        // Don't bother calculating the shortest path from the source vertex to itself.
        if (i == srcVertexIndex)
        {
            continue;
        }

        // The 'vShortestPath' vector will contain the indices of the vertices that lie on the
        // shortest path from the source vertex to the destination vertex. So this vector will
        // have 'srcVertexIndex' as the first element and 'i' as the last element.
        std::vector<unsigned int> vShortestPathIndices;

        double shortestPath = calcShortestPath(srcVertexIndex, i, vShortestPathIndices);

        // Add to the shortest paths vector only if a path actually exists.
        if (shortestPath >= 0)
        {
            vshortestPathValues.push_back(shortestPath);
        }
    }

    return (calcVectorAvg(vshortestPathValues));
}

void Graph::showEdgeListRepresentation() const
{
    unsigned int vertexIndex = 0;

    for (std::vector<Vertex>::const_iterator i = vVertices.begin(); i != vVertices.end(); ++i)
    {
        std::cout << "v" << vertexIndex << " : ";

        i->showEdgeCosts();

        ++vertexIndex;

        std::cout << std::endl;
    }
}
