#ifndef GENERATE_INSTANCE_HPP
#define GENERATE_INSTANCE_HPP

#include <vector>

#include "structures.hpp"

std::vector<std::vector<float>> generateInstance(int& totalCities, const int& areaSize, const int& choice, std::vector<Node>& cities, const char* citiesArg);

#endif // GENERATE_INSTANCE_HPP