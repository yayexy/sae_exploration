#include <iostream>
#include <fstream>
#include <vector>

#include "../include/utils.hpp"

void generateCities(int totalCities, int areaSize, std::vector<Node>& cities){
    for (int i = 0; i < totalCities; i++)
    {
        cities.emplace_back(i, 0, rand() % areaSize, rand() % areaSize);
    }
}

std::vector<std::vector<float>> calculateDistanceMatrix(const std::vector<Node>& cities, int totalCities){
    std::vector<std::vector<float>> distanceMatrix(totalCities, std::vector<float>(totalCities));

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
    
    return distanceMatrix;
}

void saveInstanceToFile(const std::vector<std::vector<float>>& distanceMatrix, const std::vector<Node>& cities, int totalCities){
    std::ofstream file("../data/input.txt");
    if (!file)
    {
        std::cerr << "Error opening the file !" << std::endl;
        return;
    }
    
    file << totalCities << std::endl;

    for (int i = 0; i < totalCities; i++)
    {
        for (int j = 0; j < totalCities; j++)
        {
            file << distanceMatrix[i][j] << " ";
        }
        
        file << std::endl;
    }
    
    // Write the coordinates of the cities to the file
    for (int i = 0; i < totalCities; i++)
    {
        file << cities[i].x << " " << cities[i].y << std::endl;
    }
    
    file.close();
}

void importInstanceFromFile(std::vector<std::vector<float>>& distanceMatrix, std::vector<Node>& cities, int& totalCities){
    std::ifstream file("../data/input.txt");
    if (!file)
    {
        std::cerr << "Error opening the file !" << std::endl;
        return;
    }
    
    file >> totalCities;
    distanceMatrix.resize(totalCities, std::vector<float>(totalCities));
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
}

std::vector<std::vector<float>> generateInstance(int& totalCities, const int& areaSize, const int& choice, std::vector<Node>& cities){
    std::vector<std::vector<float>> distanceMatrix;

    if (choice == 1)
    {
        std::cout << "Enter the number of cities: ";
        std::cin >> totalCities;

        distanceMatrix.resize(totalCities, std::vector<float>(totalCities));

        generateCities(totalCities, areaSize, cities);
        distanceMatrix = calculateDistanceMatrix(cities, totalCities);
        saveInstanceToFile(distanceMatrix, cities, totalCities);
        
        std::cout << "\nInstance generated and saved successfully!" << std::endl;
    }
    else
    {
        importInstanceFromFile(distanceMatrix, cities, totalCities);
    
        std::cout << "\nInstance imported successfully!" << std::endl;
    }

    return distanceMatrix;
}