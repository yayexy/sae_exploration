#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>

#include "../include/structures.hpp"

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

void printEulerianCircuit(std::vector<int> circuit){
    std::cout << "\nCircuit eulerien : " << std::endl;
    std::cout << "[";
    for (const int& node : circuit)
    {
        std::cout << node << ", ";
    }
    std::cout << "]" << std::endl;
}