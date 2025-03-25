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

struct Node
{
    int number;
    int degree;
    int x;
    int y;

    // Default constructor
    Node() : number(0), degree(0), x(0), y(0) {}

    // Constructor with parameters
    Node(int number, int degree = 0, int x = 0, int y = 0) : number(number), degree(degree), x(x), y(y) {}
};

struct Edge
{
    Node* start;
    Node* destination;
    float weight;
};

struct Compare {
    bool operator()(const Edge& e1, const Edge& e2){
        return e1.weight > e2.weight;
    }
};

float calculateDistance(const Node& a, const Node& b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void printEdges(const std::vector<Edge>& mst){
    std::cout << "\nAffichage des edges : " << std::endl;
    for (const Edge& edge : mst)
    {
        std::cout << "De " << edge.start->number << " à " << edge.destination->number << " avec un poids de " << edge.weight << std::endl;
    }
}

void printOddDegreeNodes(std::vector<Edge>& mst, std::vector<Node*>& odds){
    std::cout << "\nfindOddsDegree: " << std::endl;
    for (const Node* odd : odds)
    {
        std::cout << "Le degre du noeud " << odd->number << " est " << odd->degree << std::endl;
        std::cout << "Coordinates : (" << odd->x << ", " << odd->y << ")" << std::endl;
    }
}

void printNodesDegree(std::vector<Edge>& mst){
    std::cout << "\nAffichage des degres : " << std::endl;
    for (const Edge& edge : mst)
    {
        std::cout << "Node " << edge.start->number << ": degre " << edge.start->degree << std::endl;
        std::cout << "Node " << edge.destination->number << ": degre " << edge.destination->degree << std::endl;
    }
}

void printAdjacencyList(std::unordered_map<int, std::vector<int>> adjList){
    std::cout << "\nListe d'adjacence : " << std::endl;
    for (int i = 0; i < adjList.size(); i++)
    {
        std::cout << "Noeud " << i << " : [";
        for (int j = 0; j < adjList[i].size(); j++)
        {
            std::cout << adjList[i][j] << ", ";
        }
        std::cout << "]" << std::endl;
    }
}

std::vector<std::vector<float>> generateInstance(int& totalCities, const int& areaSize, const int& choice, std::vector<Node>& cities){
    std::vector<std::vector<float>> distanceMatrix;

    if (choice == 1)
    {
        std::cout << "Enter the number of cities: ";
        std::cin >> totalCities;

        distanceMatrix.resize(totalCities, std::vector<float>(totalCities));

        // Randomly generating cities
        for (int i = 0; i < totalCities; i++)
        {
            cities.emplace_back(i, 0, rand() % areaSize, rand() % areaSize); // Now I can create Node objects (I have access to number)
        }

        for (int i = 0; i < totalCities; i++)
        {
            for (int j = 0; j < totalCities; j++)
            {
                if (i == j)
                {
                    distanceMatrix[i][j] = 0;
                }
                else
                {
                    distanceMatrix[i][j] = calculateDistance(cities[i], cities[j]);
                }
            }
        }
        
        // Opening the file to write the instance
        std::ofstream file("instance.txt");
        if (!file)
        {
            std::cerr << "Error opening the file!" << std::endl;
            return distanceMatrix;
        }

        file << totalCities << std::endl;

        for (int i = 0; i < totalCities; i++)
        {
            for (int j = 0; j < totalCities; j++)
            {
                if (i == j)
                {
                    file << "0 ";
                }
                else
                {
                    file << calculateDistance(cities[i], cities[j]) << " ";
                }
            }
            file << std::endl;
        }

        // Write the coordinates of the cities to the file
        for (int i = 0; i < totalCities; i++)
        {
            file << cities[i].x << " " << cities[i].y << std::endl;
        }

        file.close();
        std::cout << "\nInstance generated and saved successfully!" << std::endl;
    }
    else
    {
        std::ifstream file("instance.txt");
        if (!file)
        {
            std::cerr << "Error opening the file!" << std::endl;
            return distanceMatrix;
        }
        
        file >> totalCities;
        distanceMatrix.resize(totalCities, std::vector<float>(totalCities));
        
        cities.clear();
        cities.resize(totalCities);

        for (int i = 0; i < totalCities; i++)
        {
            for (int j = 0; j < totalCities; j++)
            {
                file >> distanceMatrix[i][j];
            }
        }

        for (int i = 0; i < totalCities; i++)
        {
            file >> cities[i].x >> cities[i].y;
            cities[i].number = i;
            cities[i].degree = 0;
        }

        file.close();
        std::cout << "\nInstance imported successfully!" << std::endl;
    }

    return distanceMatrix;
}

std::vector<Edge> primAlgorithm(const int& totalCities, const std::vector<std::vector<float>>& distanceMatrix, std::vector<Node>& cities) {
    std::vector<Edge> mst; // Stores the edges of the Minimum Spanning Tree (MST)
    std::vector<bool> inMST(totalCities, false); // Tracks whether a node is included in the MST
    std::priority_queue<Edge, std::vector<Edge>, Compare> pq; // Priority queue (min-heap)

    inMST[0] = true;
    for (int i = 1; i < totalCities; i++)
    {
        pq.push({&cities[0], &cities[i], distanceMatrix[0][i]});
    }
    
    while (!pq.empty() && mst.size() < totalCities - 1)
    {
        Edge edge = pq.top();
        pq.pop();

        int u = edge.destination->number;
        if (inMST[u])
        {
            continue;
        }
        
        inMST[u] = true;
        mst.push_back(edge);

        edge.start->degree++;
        edge.destination->degree++;
        
        for (int v = 0; v < totalCities; v++)
        {
            if (!inMST[v])
            {
                pq.push({edge.destination, &cities[v], distanceMatrix[u][v]});
            }
        }
    }

    return mst;
}

std::vector<Node*> findOddsDegreeNodes(std::vector<Edge>& mst){
    std::unordered_map<int, Node*> nodeMap;
    std::unordered_map<int, int> degreeMap;

    for (const Edge& edge : mst)
    {
        nodeMap[edge.start->number] = edge.start;
        nodeMap[edge.destination->number] = edge.destination;

        degreeMap[edge.start->number]++;
        degreeMap[edge.destination->number]++;
    }

    std::vector<Node*> oddNodes;
    for (const auto& pair : degreeMap)
    {
        if (pair.second % 2 == 1)
        {
            oddNodes.push_back(nodeMap[pair.first]);
        }
    }
    
    return oddNodes;
}

void perfectMatching(std::vector<Edge>& mst, std::vector<Node*>& odds){
    std::unordered_map<int, int> degreeMap;

    while (!odds.empty())
    {
        Node* start = odds.back();
        odds.pop_back();

        Node* closest = nullptr;
        float weight = std::numeric_limits<float>::max();

        for (Node* destination : odds)
        {
            if (calculateDistance(*start, *destination) < weight)
            {
                weight = calculateDistance(*start, *destination);
                closest = destination;
            }
        }
        
        if (closest)
        {
            mst.push_back({start, closest, weight});
            start->degree++;
            closest->degree++;

            odds.erase(std::remove(odds.begin(), odds.end(), closest), odds.end());
        }
    }

    // Étape 2 : Vérifier si des noeuds sont encore impairs et donc les supprimer
    for (const Edge& edge : mst)
    {
        degreeMap[edge.start->number]++;
        degreeMap[edge.destination->number]++;
    }
    
    std::vector<Edge> filteredEdges;
    for (const Edge& edge : mst)
    {
        if (degreeMap[edge.start->number] % 2 == 1 && degreeMap[edge.destination->number] % 2 == 1)
        {
            degreeMap[edge.start->number]--;
            degreeMap[edge.destination->number]--;
        }
        else
        {
            filteredEdges.push_back(edge);
        }
    }
    
    mst = filteredEdges;
}

std::vector<int> findEulerianCircuit(const std::vector<Edge>& mst, const int& totalCities){
    std::vector<int> circuit; // This will store the Eulerian Circuit
    std::stack<int> stack;
    std::unordered_map<int, std::vector<int>> adjList;

    int curr_v = 0;

    for (const Edge& edge : mst)
    {
        adjList[edge.start->number].push_back(edge.destination->number);
        adjList[edge.destination->number].push_back(edge.start->number);
    }
    
    printAdjacencyList(adjList);

    return circuit;
}

// std::vector<int> findEulerianCircuit(const std::vector<Edge>& mst, const int& totalCities){
//     std::vector<bool> inEulerianCircuit(totalCities, false); // Tracks whether a node is included in the circuit
//     std::vector<int> circuit;  // This will store the Eulerian Circuit
//     std::stack<Node*> stack;
//     std::unordered_map<int, std::vector<Edge>> adjList;

//     // Fill the adjList with MST edges
//     for (const Edge& edge : mst) {
//         adjList[edge.start->number].push_back(edge);
//         adjList[edge.destination->number].push_back(edge);
//     }
    
//     // Start circuit with the node 0
//     stack.push(mst[0].start);

//     while (!stack.empty()) {
//         Node* currentNode = stack.top();

//         if (!adjList[currentNode->number].empty()) { // If the node still has neighbors
//             // Get the last edge in the adjacency list
//             Edge edge = adjList[currentNode->number].back();
//             adjList[currentNode->number].pop_back();

//             // Remove the edge from the destination node's adjacency list as well
//             adjList[edge.destination->number].erase(
//                 std::remove_if(adjList[edge.destination->number].begin(), adjList[edge.destination->number].end(),
//                                [&](const Edge& e) { return e.start == edge.start && e.destination == edge.destination; }),
//                 adjList[edge.destination->number].end());

//             // Add current node to the circuit (only when you move to a new node)
//             if (!inEulerianCircuit[currentNode->number]) {
//                 circuit.push_back(currentNode->number);
//                 inEulerianCircuit[currentNode->number] = true;
//             }

//             // Move to the next node
//             stack.push(edge.destination);
//         } else { // If the node has no more neighbors, add it to the circuit and backtrack
//             circuit.push_back(currentNode->number);
//             stack.pop();
//         }
//     }

//     return circuit;
// }

// std::vector<int> findHamiltonianCycle(const std::vector<Node>& cities){

// }

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

    return 0;
}