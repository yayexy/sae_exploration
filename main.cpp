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
            odds.erase(std::remove(odds.begin(), odds.end(), closest), odds.end());
        }
    }
}

int main(){
    srand(time(NULL));

    int areaSize = 1000;
    int totalCities;
    int choice;
    std::vector<Node> cities; // Changed to store Node objects directly

    do
    {
        std::cout << "Do you want to create a new graph or use an existing one? (1 - Yes / 0 - No): ";
        std::cin >> choice;
    } while (choice != 0 && choice != 1);
    
    std::vector<std::vector<float>> distanceMatrix = generateInstance(totalCities, areaSize, choice, cities);

    std::vector<Edge> mst = primAlgorithm(totalCities, distanceMatrix, cities);
    
    std::cout << std::endl;
    std::cout << "Affichage des edges : " << std::endl;
    for (const Edge& edge : mst)
    {
        std::cout << "De " << edge.start->number << " à " << edge.destination->number << " avec un poids de " << edge.weight << std::endl;
    }

    std::cout << std::endl;

    std::cout << "Affichage des degres : " << std::endl;
    for (const Edge& edge : mst)
    {
        std::cout << "Node " << edge.start->number << ": degre " << edge.start->degree << std::endl;
        std::cout << "Node " << edge.destination->number << ": degre " << edge.destination->degree << std::endl;
    }

    std::cout << "\n\nfindOddsDegree: " << std::endl;
    std::vector<Node*> odds = findOddsDegreeNodes(mst);

    for (const Node* odd : odds)
    {
        std::cout << "Le degre du noeud " << odd->number << " est " << odd->degree << std::endl;
        std::cout << "Coordinates : (" << odd->x << ", " << odd->y << ")" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Affichage des edges (avant) : " << std::endl;
    for (const Edge& edge : mst)
    {
        std::cout << "De " << edge.start->number << " à " << edge.destination->number << " avec un poids de " << edge.weight << std::endl;
    }

    perfectMatching(mst, odds);

    std::cout << std::endl;
    std::cout << "Affichage des edges (apres) : " << std::endl;
    for (const Edge& edge : mst)
    {
        std::cout << "De " << edge.start->number << " à " << edge.destination->number << " avec un poids de " << edge.weight << std::endl;
    }

    return 0;
}
