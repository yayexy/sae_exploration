#include <iostream>
#include <fstream>
#include <vector>

#include "../include/utils.hpp"

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
        std::ofstream file("../data/input.txt");
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
        std::ifstream file("../data/input.txt");
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