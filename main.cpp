#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <queue>
#include <unordered_map>

struct City
{
    int x;
    int y;
};

struct Node
{
    int number;
    int degree;

    Node(int number, int degree = 0): number(number), degree(degree) {}
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

float calculateDistance(const City& a, const City& b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

std::vector<std::vector<float>> generateInstance(int& totalCities, const int& areaSize, const int& choice){
    std::vector<std::vector<float>> distanceMatrix;

    if (choice == 1)
    {
        std::cout << "Enter the number of cities: ";
        std::cin >> totalCities;

        distanceMatrix.resize(totalCities, std::vector<float>(totalCities));
        std::vector<City> cities(totalCities);

        // Randomly generating city coordinates
        for (int i = 0; i < totalCities; i++)
        {
            cities[i].x = rand() % areaSize;
            cities[i].y = rand() % areaSize;
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
        
        for (int i = 0; i < totalCities; i++)
        {
            for (int j = 0; j < totalCities; j++)
            {
                file >> distanceMatrix[i][j];
            }
        }

        file.close();
        std::cout << "\nInstance imported successfully!" << std::endl;
    }

    return distanceMatrix;
}

std::vector<Edge> primAlgorithm(const int& totalCities, const std::vector<std::vector<float>>& distanceMatrix) {
    std::vector<Edge> mst; // Stores the edges of the Minimum Spanning Tree (MST)
    std::vector<bool> inMST(totalCities, false); // Tracks whether a node is included in the MST
    std::priority_queue<Edge, std::vector<Edge>, Compare> pq; // Priority queue (min-heap)

    inMST[0] = true;
    for (int i = 1; i < totalCities; i++)
    {
        Node* startCity = new Node(0, 0);
        Node* destinationCity = new Node(i, 0);
        pq.push({startCity, destinationCity, distanceMatrix[0][i]});
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
                Node* startCity = edge.destination;
                Node* destinationCity = new Node(v, 0);
                pq.push({startCity, destinationCity, distanceMatrix[u][v]});
            }
        }
    }
    
    return mst;
}

// bool findInOddsList(std::vector<Node*> odds, int number){
//     for (const Node& node : odds)
//     {
//         if (node.number == number)
//         {
//             return true;
//         }
//     }

//     return false;
// }

std::vector<Node*> findOddsDegreeNodes(std::vector<Edge> mst){
    std::cout << "\n\nfindOddsDegree: " << std::endl;
    
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

int main(){
    srand(time(NULL));

    int areaSize = 1000;
    int totalCities;
    int choice;

    do
    {
        std::cout << "Do you want to create a new graph or use an existing one? (1 - Yes / 0 - No): ";
        std::cin >> choice;
    } while (choice != 0 && choice != 1);
    
    std::vector<std::vector<float>> distanceMatrix = generateInstance(totalCities, areaSize, choice);

    std::vector<Edge> mst = primAlgorithm(totalCities, distanceMatrix);
    
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

    std::vector<Node*> odds = findOddsDegreeNodes(mst);

    for (const Node* odd : odds)
    {
        std::cout << "Le degre du noeud " << odd->number << " est " << odd->degree << std::endl;
    }
    
    return 0;
}
