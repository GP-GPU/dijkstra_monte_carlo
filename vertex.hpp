#pragma once

#include <vector>

class Vertex
{
private:
    std::vector<int> vEdgeCosts;

public:
    Vertex();
    void setEdgeCost(unsigned int, double);
    void showEdgeCosts() const;
    bool edgeAlreadyExists(unsigned int) const;
};
