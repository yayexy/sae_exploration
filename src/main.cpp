#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <string>
#include <chrono>

#include "../include/structures.hpp"
#include "../include/utils.hpp"
#include "../include/generateInstance.hpp"
#include "../include/mst.hpp"
#include "../include/christofides.hpp"

int main(int argc, char* argv[]) {
    auto start = std::chrono::high_resolution_clock::now();
    srand(time(NULL));

    int areaSize = 1000;
    int totalCities;
    int choice;
    std::vector<Node> cities; 
    std::vector<int> circuit; 
    std::vector<int> cycle;

    // --- INPUT METHOD ---
    if (argc == 2 || argc == 3) {
        try {
            choice = std::stoi(argv[1]);
            // std::cout << "Choice (from argument): " << choice << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Invalid argument!" << std::endl;
            return 1;
        }
    } else {
        do {
            std::cout << "Create a new graph or use existing one? (1 - Yes / 0 - No): ";
            std::cin >> choice;
        } while (choice != 0 && choice != 1); 
    }

    const char* citiesArg = (argc == 3) ? argv[2] : nullptr;
    std::vector<std::vector<float>> distanceMatrix = generateInstance(totalCities, areaSize, choice, cities, citiesArg);

    // --- MST ---
    std::vector<Edge> mst = primAlgorithm(totalCities, distanceMatrix, cities);
    // printEdges(mst);
    // printNodesDegree(mst);

    // --- FIND ODD DEGREE NODES ---
    std::vector<Node*> odds = findOddsDegreeNodes(mst);
    // printOddDegreeNodes(mst, odds);

    // --- PERFECT MATCHING ---
    perfectMatching(mst, odds);
    // printEdges(mst);
    // printNodesDegree(mst);

    // --- EULERIAN CIRCUIT ---
    circuit = findEulerianCircuit(mst, totalCities);
    // printEulerianCircuit(circuit);

    // --- HAMILTONIAN CYCLE ---
    cycle = findHamiltonianCycle(circuit, cities);

    // --- DISPLAY FINAL RESULTS ---
    std::cout << "\n=== Hamiltonian Cycle ===\n";
    printHamiltonianCycle(cycle);

    float cost = calculateTotalCost(cycle, distanceMatrix);
    std::cout << "Total cost: " << cost << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Execution time: " << elapsed.count() << " s\n";

    printFinalResult(cycle, distanceMatrix);

    return 0;
}
