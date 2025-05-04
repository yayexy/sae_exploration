#include <vector>
#include <stack>
#include <limits>
#include <algorithm>
#include <unordered_set>

#include "../include/utils.hpp"

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

std::vector<int> findEulerianCircuit(std::vector<Edge>& mst, int totalCities) {
    std::unordered_map<int, std::vector<int>> adjacencyList; // Adjacency list with node neighbors
    std::vector<int> circuit;  
    std::stack<int> stack;

    // Build the adjacency list
    for (const Edge& edge : mst) {
        adjacencyList[edge.start->number].push_back(edge.destination->number);
        adjacencyList[edge.destination->number].push_back(edge.start->number);
    }

    // Find a valid starting node (a node with at least one edge)
    int startNode = mst[0].start->number; 
    stack.push(startNode);

    while (!stack.empty()) {
        int currentNode = stack.top();

        // If the node still has neighbors
        if (!adjacencyList[currentNode].empty()) {
            int nextNode = adjacencyList[currentNode].back();  // Last neighbor
            adjacencyList[currentNode].pop_back();  // Remove the edge (current -> next)

            // Also remove the edge in the opposite direction (next -> current)
            auto& neighbors = adjacencyList[nextNode];
            neighbors.erase(std::find(neighbors.begin(), neighbors.end(), currentNode));

            stack.push(nextNode); // Move to the next node
        } else {
            // If no more neighbors, add the node to the final circuit and backtrack
            circuit.push_back(currentNode);
            stack.pop();
        }
    }

    return circuit;
}

std::vector<int> findHamiltonianCycle(const std::vector<int>& circuit, const std::vector<Node>& cities) {
    std::vector<int> hamiltonian;
    std::unordered_set<int> visited;

    for (int cityIndex : circuit) {
        if (visited.find(cityIndex) == visited.end()) {
            visited.insert(cityIndex);
            hamiltonian.push_back(cityIndex);
        }
    }

    return hamiltonian;
}