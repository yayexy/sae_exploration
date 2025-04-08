#ifndef CHRISTOFIDES_HPP
#define CHRISTOFIDES_HPP

#include <vector>

#include "../include/utils.hpp"

std::vector<Node*> findOddsDegreeNodes(std::vector<Edge>& mst);
void perfectMatching(std::vector<Edge>& mst, std::vector<Node*>& odds);
std::vector<int> findEulerianCircuit(std::vector<Edge>& mst, int totalCities);
std::vector<int> findHamiltonianCycle(const std::vector<int>& circuit, const std::vector<Node>& cities);

#endif // CHRISTOFIDES_HPP