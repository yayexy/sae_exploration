#include <vector>
#include <queue>

#include "../include/structures.hpp"

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