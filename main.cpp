#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

struct City
{
    int x;
    int y;
};

// struct Edge
// {
//     int weight;
//     int start;
//     int destination;
// };

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

std::vector<int> primAlgorithm(const int& totalCities, const std::vector<std::vector<float>>& distanceMatrix){
    // stores the edges of the mst
    std::vector<int> mst;
    // stores if a node is included in the mst
    std::vector<bool> inMST(totalCities, false);

    return mst;
}

int main(){
    srand(time(NULL));

    int areaSize = 1000;

    int totalCities;
    std::cout << "Enter the number of cities: ";
    std::cin >> totalCities;

    std::vector<std::vector<float>> distanceMatrix = generateInstance(totalCities, areaSize);
    
    std::vector<int> mst = primAlgorithm(totalCities, distanceMatrix);
    
    return 0;
}
