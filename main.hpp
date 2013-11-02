#pragma once

#include <vector>

const unsigned int NUM_GRAPHS = 10;
const unsigned int NUM_VERTICES_IN_GRAPH = 50;
const bool SELF_LOOPS_ALLOWED = false;
const double EDGE_DENSITY = 0.4;
const double MIN_EDGE_COST = 1.0;
const double MAX_EDGE_COST = 10.0;
const bool SHOW_AVG_SHORTEST_PATH_PER_GRAPH = true;

double calcVectorAvg(const std::vector<double>&);
