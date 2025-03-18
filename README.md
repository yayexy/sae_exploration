SAÉ S2.02 - Exploration Algorithmique du Problème du Voyageur de Commerce
📌 Description
Ce projet a pour objectif d'explorer différentes approches algorithmiques pour résoudre le problème du voyageur de commerce (Traveling Salesman Problem - TSP). Ce problème consiste à trouver le chemin le plus court passant par un ensemble de villes (ou restaurants dans notre cas) exactement une seule fois avant de revenir au point de départ.

🎯 Objectifs
Générer des instances du problème (coordonnées aléatoires de villes/restaurants).
Construire et manipuler une matrice de distances entre ces villes.
Implémenter et comparer différents algorithmes de résolution.
Évaluer les performances des algorithmes en termes de qualité de solution et de temps de calcul.
⚙️ Fonctionnalités
✅ Générateur d'instances :

Génération aléatoire des coordonnées des villes.
Calcul des distances entre chaque paire de villes.
Sauvegarde et lecture des instances dans un fichier.
✅ Algorithmes implémentés :

Prim’s Algorithm : Construction d’un Arbre Recouvrant Minimal (MST) utilisé pour approximer la solution du TSP.
Autres algorithmes (à compléter selon les besoins) :
Glouton (Greedy)
2-opt
Colonie de Fourmis
Algorithme Génétique
✅ Comparaison des solutions :

Évaluation du coût total des parcours générés.
Analyse des performances des algorithmes.
📂 Structure du projet
graphql
Copy
Edit
📁 SAÉ_S2_02
│── 📄 main.cpp          # Programme principal
│── 📄 generateInstance.cpp  # Génération des instances
│── 📄 primAlgorithm.cpp     # Implémentation de l'algorithme de Prim
│── 📄 utils.cpp        # Fonctions utilitaires (calcul de distances, affichage, etc.)
│── 📄 input.txt        # Fichier contenant une instance du TSP
│── 📄 output.txt       # Résultat de l'algorithme (ordre des villes visitées)
│── 📄 README.md        # Documentation du projet
