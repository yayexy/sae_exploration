# SAÉ S2.02 - Exploration Algorithmique du TSP (Christofides)

## 📝 Description
Ce projet consiste à implémenter l'algorithme de Christofides pour résoudre le problème du voyageur de commerce (Traveling Salesman Problem - TSP).
L'algorithme suit trois grandes étapes :

- Construction d'un Arbre Recouvrant Minimal (MST) ✅ (Actuellement implémenté)
- Trouver les sommets de degré impair & construire un appariement parfait
- Créer un circuit eulérien et transformer la solution en un tour valide du TSP

## 🎯 Objectifs
- Générer et manipuler une matrice de distances.
- Implémenter Christofides étape par étape.
- Comparer les performances avec d'autres méthodes d’approximation.

## ⚙️ Fonctionnalités
✅ Générateur d'instances (coordonnées aléatoires, calcul des distances, sauvegarde/lecture fichier)  
✅ Algorithme de Prim (MST) (Première étape de Christofides)  
🔄 À venir :

- Détection des sommets impairs & appariement parfait
- Construction du circuit eulérien
- Transformation en un tour TSP valide

## 📂 Structure du projet
```graphql
📁 SAÉ_S2_02
│── 📄 main.cpp          # Programme principal
│── 📄 generateInstance.cpp  # Génération des instances
│── 📄 mst.cpp           # Algorithme de Prim (MST)
│── 📄 christofides.cpp  # Implémentation complète de Christofides (en cours)
│── 📄 utils.cpp         # Fonctions utilitaires (calcul de distances, affichage, etc.)
│── 📄 input.txt         # Fichier contenant une instance du TSP
│── 📄 output.txt        # Résultat final du TSP
│── 📄 README.md         # Documentation du projet
```

## 🚀 Installation et Exécution
1️⃣ Compilation
```bash
g++ -o tsp main.cpp generateInstance.cpp mst.cpp christofides.cpp utils.cpp -O2
```

2️⃣ Exécution
```bash
./tsp
```

- Créer un nouveau graphe avec des villes aléatoires.
- Utiliser une instance existante (fichier input.txt).

## 📊 Critères d'évaluation
- Qualité du parcours obtenu (Comparaison avec d'autres heuristiques)
- Temps de calcul (Efficacité de l'algorithme sur des instances de grande taille)

## 👥 Auteurs
whoselevenn  

Projet réalisé dans le cadre du B.U.T. Informatique - SAÉ S2.02 🎓🚀

