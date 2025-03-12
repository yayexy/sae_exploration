#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <cmath>

struct Ville
{
    int x;
    int y;
};

float calculerDistance(const Ville& a, const Ville& b){
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

int main(){
    srand(time(NULL));

    int tailleZone = 1000;

    int nombreVilles;
    std::cout << "Entrez le nombre de villes : ";
    std::cin >> nombreVilles;

    std::vector<Ville> villes(nombreVilles);

    // Génération aléatoire des coordonnées des villes
    for (int i = 0; i < nombreVilles; i++)
    {
        villes[i].x = rand() % tailleZone;
        villes[i].y = rand() % tailleZone;
    }
    
    // Ouverture du fichier pour écrire l'instance
    std::ofstream fichier("instance.txt");
    if (!fichier)
    {
        std::cerr << "Erreur lors de l'ouverture du fichier !" << std::endl;
        return 1;
    }

    fichier << nombreVilles << std::endl;

    for (int i = 0; i < nombreVilles; i++)
    {
        for (int j = 0; j < nombreVilles; j++)
        {
            if (i == j)
            {
                fichier << "0 ";
            }
            else
            {
                fichier << calculerDistance(villes[i], villes[j]) << " ";
            }
        }
        fichier << std::endl;
    }
    
    fichier << std::endl;

    for (int i = 0; i < nombreVilles; i++) {
        fichier << "Ville " << i << " : x = " << villes[i].x << " / y = " << villes[i].y << std::endl;
    }

    fichier.close();
    std::cout << "Instance générée et sauvegardée avec succès !" << std::endl;

    return 0;
}