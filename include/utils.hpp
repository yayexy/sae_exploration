#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <unordered_map>

#include "structures.hpp"

float calculateDistance(const Node& a, const Node& b);

void printEdges(const std::vector<Edge>& mst);
void printOddDegreeNodes(std::vector<Edge>& mst, std::vector<Node*>& odds);
void printNodesDegree(std::vector<Edge>& mst);
void printAdjacencyList(std::unordered_map<int, std::vector<int>> adjList);
void printEulerianCircuit(std::vector<int> circuit);
void printHamiltonianCycle(std::vector<int> circuit);
float calculateTotalCost(const std::vector<int>& cycle, const std::vector<std::vector<float>>& distanceMatrix);


#endif // UTILS_HPP