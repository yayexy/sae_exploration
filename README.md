# SAÉ S2.02 - Exploration Algorithmique du TSP (Christofides)

## ❓ Problème
Les vacances d’été arrivent et vos enseignants ont décidé de les mettre à
profit pour être productifs ! Ils souhaitent manger dans chacun des 190
restaurants du département pour décider lequel est le meilleur (O’puits
grand favori). Cependant, ils ne veulent pas perdre trop de temps à se
déplacer, car le temps c’est du manger. Comment pouvons vous les aider ?

## 📝 Description
Ce projet consiste à implémenter un algorithme pour résoudre le problème du voyageur de commerce (Traveling Salesman Problem - TSP). Ainsi, j'ai choisi l'algorithme de Christofides.
L'algorithme suit trois grandes étapes :

- Construction d'un Arbre Recouvrant Minimal (MST)
- Trouver les sommets de degré impair & construire un appariement parfait
- Créer un circuit eulérien et transformer la solution en un cycle hamiltonien valide du TSP

## 🎯 Objectifs
- Générer et manipuler une matrice de distances.
- Implémenter Christofides étape par étape.
- Comparer les performances avec d'autres méthodes d’approximation des membres de l'équipe.

## ⚙️ Fonctionnalités
✅ Générateur d'instances (coordonnées aléatoires, calcul des distances, sauvegarde/lecture fichier)  
✅ Algorithme de Prim (MST)  
✅ Détection des sommets impairs & appariement parfait  
✅ Construction du circuit eulérien  
✅ Transformation en un tour TSP valide  

## 📂 Structure du projet
```graphql
📁 SAÉ_S2_02
│
│── 📁 src
│ │── 📄 main.cpp              # Programme principal
│ │── 📄 mst.cpp               # Algorithme de Prim (MST)
│ │── 📄 christofides.cpp      # Algorithme de Christofides
│ │── 📄 generateInstance.cpp  # Génération des instances
│ │── 📄 utils.cpp             # Fonctions utilitaires
│
│── 📁 include
│ │── 📄 mst.hpp               # Header de l'algorithme de Prim (MST)
│ │── 📄 christofides.hpp      # Header de l'algorithme de Christofides
│ │── 📄 generateInstance.hpp  # Header du générateur d'instances
│ │── 📄 utils.hpp             # Header des fonctions utilitaires
│ │── 📄 structures.hpp        # Définition des structures Node, Edge, Compare
│
│── 📁 data
│ │── 📄 input.txt             # Instance du problème TSP
│ │── 📄 output.txt            # Sortie du problème TSP
│
│── 📄 README.md               # Documentation du projet
│── 📄 Makefile                # Compilation du projet
```

## 🚀 Installation et Exécution
1️⃣ Compilation
```bash
g++ -o main main.cpp
```

2️⃣ Exécution
```bash
./main
```

- Créer un nouveau graphe avec des villes aléatoires.
- Utiliser une instance existante (fichier input.txt).

## 📊 Critères d'évaluation
- Qualité du parcours obtenu (Comparaison avec d'autres heuristiques)
- Temps de calcul (Efficacité de l'algorithme sur des instances de grande taille)

## 👥 Auteurs
whoselevenn  

Projet réalisé dans le cadre du B.U.T. Informatique - SAÉ S2.02 🎓🚀
