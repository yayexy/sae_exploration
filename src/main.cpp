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

#include "../include/structures.hpp"
#include "../include/utils.hpp"
#include "../include/generateInstance.hpp"
#include "../include/mst.hpp"
#include "../include/christofides.hpp"

int main() {
    srand(time(NULL));

    int areaSize = 1000;
    int totalCities;
    int choice;
    std::vector<Node> cities; 
    std::vector<int> circuit; // Stocke le circuit eulérien

    // --- CHOIX DU MODE DE GÉNÉRATION DU GRAPHE ---
    do {
        std::cout << "Do you want to create a new graph or use an existing one? (1 - Yes / 0 - No): ";
        std::cin >> choice;
    } while (choice != 0 && choice != 1);

    // --- GÉNÉRATION DU GRAPHE ---
    std::vector<std::vector<float>> distanceMatrix = generateInstance(totalCities, areaSize, choice, cities);

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

    return 0;
}