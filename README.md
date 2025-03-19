# SAE 2 Graph

Ce projet implémente un programme d'optimisation basé sur les algorithmes **2-opt** et **3-opt**, utilisés pour résoudre des problèmes d'optimisation combinatoire, comme le célèbre problème du voyageur de commerce (TSP - Travelling Salesman Problem).
Dans cette SAE le problème posé est le suivant :
190 restaurants dans la Nièvre, on cherche le plus court chemin pour tous les visiter.

## Fonctionnement

1. **Phase 1 : Optimisation 2-opt**  
   Le programme commence par appliquer l'algorithme 2-opt pour améliorer une solution initiale. Cet algorithme consiste à échanger deux arêtes dans le chemin pour réduire la distance totale.

2. **Phase 2 : Optimisation 3-opt**  
   Si l'algorithme 2-opt ne permet plus d'améliorer la solution, le programme passe à l'algorithme 3-opt. Celui-ci effectue des échanges impliquant trois arêtes pour explorer davantage de possibilités d'amélioration.

3. **Phase 3 : Retour au 2-opt**  
   Si le 3-opt trouve une meilleure solution, le programme revient à une phase de 2-opt pour affiner cette nouvelle solution.

## Objectif

L'objectif principal est de trouver une solution optimale ou quasi-optimale en combinant ces deux algorithmes de manière itérative et stratégique.

## Applications

Ce projet peut être utilisé pour résoudre des problèmes d'optimisation dans divers domaines, tels que :
- La logistique (optimisation des itinéraires de livraison)
- La planification (minimisation des coûts de déplacement)
- Les réseaux (optimisation des chemins dans un graphe)

---

Ce projet est une excellente opportunité pour explorer des algorithmes d'optimisation avancés et leur application dans des problèmes réels.