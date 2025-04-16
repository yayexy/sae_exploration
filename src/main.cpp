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
    std::vector<int> circuit; // Stocke le circuit eulérien
    std::vector<int> cycle;

    // --- CHOIX DU MODE DE GÉNÉRATION DU GRAPHE ---
    if (argc == 2 || argc == 3) // 2 if the choice is 0, don't need the second argument. Otherwise, 2 arguments needed if argument 1 is 1
    {
        try 
        {
            choice = std::stoi(argv[1]);
            std::cout << "Choice (from argument) : " << choice << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Erreur ! L'argument est invalide ! " << std::endl;
            return 1;
        }
    }
    else
    {
        do {
            std::cout << "Do you want to create a new graph or use an existing one? (1 - Yes / 0 - No): ";
            std::cin >> choice;
        } while (choice != 0 && choice != 1); 
    }

    // --- GÉNÉRATION DU GRAPHE ---
    const char* citiesArg = (argc == 3) ? argv[2] : nullptr;
    std::vector<std::vector<float>> distanceMatrix = generateInstance(totalCities, areaSize, choice, cities, citiesArg);

    // --- CALCUL DE L'ARBRE COUVRANT MINIMAL (MST) ---
    std::vector<Edge> mst = primAlgorithm(totalCities, distanceMatrix, cities);
    
    std::cout << "\n=== Arbre couvrant minimal (MST) ===\n";
    printEdges(mst);
    printNodesDegree(mst);

    // --- IDENTIFICATION DES NŒUDS DE DEGRÉ IMPAIR ---
    std::vector<Node*> odds = findOddsDegreeNodes(mst);
    
    std::cout << "\n=== Noeuds de degre impair ===\n";
    printOddDegreeNodes(mst, odds);

    // --- APPLICATION DU PERFECT MATCHING ---
    perfectMatching(mst, odds);

    std::cout << "\n=== Graphe apres Perfect Matching ===\n";
    printEdges(mst);
    printNodesDegree(mst);

    // --- CALCUL DU CIRCUIT EULÉRIEN ---
    std::cout << "\n=== Circuit Eulerien ===\n";
    circuit = findEulerianCircuit(mst, totalCities);
    printEulerianCircuit(circuit);

    // --- CALCUL DU CYCLE HAMILTONIEN ---
    std::cout << "\n=== Cycle Hamiltonien ===\n";
    cycle = findHamiltonianCycle(circuit, cities);
    printHamiltonianCycle(cycle);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nExecution time: " << elapsed.count() << " s\n";

    return 0;
}