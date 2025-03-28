#ifndef MST_HPP
#define MST_HPP

#include <vector>

#include "structures.hpp"

std::vector<Edge> primAlgorithm(const int& totalCities, const std::vector<std::vector<float>>& distanceMatrix, std::vector<Node>& cities);

#endif // MST_HPP