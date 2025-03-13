#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>

#include <queue>

struct City
{
    int x;
    int y;
};

struct Edge
{
    int start;
    int destination;
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

std::vector<std::vector<float>> generateInstance(const int& totalCities, const int& areaSize){
    std::vector<City> cities(totalCities);
    std::vector<std::vector<float>> distanceMatrix(totalCities, std::vector<float>(totalCities));

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
    
    file << std::endl;

    for (int i = 0; i < totalCities; i++) {
        file << "City " << i << " : x = " << cities[i].x << " / y = " << cities[i].y << std::endl;
    }

    file.close();
    std::cout << "Instance generated and saved successfully!" << std::endl;

    return distanceMatrix;
}

std::vector<Edge> primAlgorithm(const int& totalCities, const std::vector<std::vector<float>>& distanceMatrix) {
    std::vector<Edge> mst; // Stores the edges of the Minimum Spanning Tree (MST)
    std::vector<bool> inMST(totalCities, false); // Tracks whether a node is included in the MST
    std::priority_queue<Edge, std::vector<Edge>, Compare> pq; // Priority queue (min-heap)

    inMST[0] = true;
    for (int i = 1; i < totalCities; i++)
    {
        pq.push({0, i, distanceMatrix[0][i]});
    }
    
    while (!pq.empty() && mst.size() < totalCities - 1)
    {
        Edge edge = pq.top();
        pq.pop();

        int u = edge.destination;
        if (inMST[u])
        {
            continue;
        }
        
        inMST[u] = true;
        mst.push_back(edge);

        for (int v = 0; v < totalCities; v++)
        {
            if (!inMST[v])
            {
                pq.push({u, v, distanceMatrix[u][v]});
            }
        }
    }
    
    return mst;
}


int main(){
    srand(time(NULL));

    int areaSize = 1000;

    int totalCities;
    std::cout << "Enter the number of cities: ";
    std::cin >> totalCities;

    std::vector<std::vector<float>> distanceMatrix = generateInstance(totalCities, areaSize);
    
    // std::vector<std::vector<float>> distanceMatrix = {
    //     {0, 757.341, 339.236, 735.218, 424.449},
    //     {757.341, 0, 587.231, 365.308, 441.38},
    //     {339.236, 587.231, 0, 431.335, 148.189},
    //     {735.218, 365.308, 431.335, 0, 311.04},
    //     {424.449, 441.38, 148.189, 311.04, 0}
    // };

    std::vector<Edge> mst = primAlgorithm(totalCities, distanceMatrix);
    
    for (const Edge& edge : mst)
    {
        std::cout << "De " << edge.start << " à " << edge.destination << " avec un poids de " << edge.weight << std::endl;
    }
    
    return 0;
}
