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

## Détails de l'algorithme 2-opt

L'algorithme 2-opt est une méthode d'optimisation locale utilisée pour améliorer une solution initiale au problème du voyageur de commerce. Son fonctionnement repose sur les étapes suivantes :

1. **Initialisation**  
   On part d'une solution initiale, qui peut être un chemin quelconque reliant tous les points (par exemple, un chemin généré aléatoirement ou une solution heuristique).

2. **Recherche d'améliorations**  
   L'algorithme parcourt toutes les paires d'arêtes dans le chemin actuel. Pour chaque paire, il effectue un échange (ou "2-opt swap") en inversant l'ordre des nœuds entre ces deux arêtes.

3. **Évaluation**  
   Après chaque échange, la nouvelle solution est évaluée en calculant la distance totale du chemin. Si la nouvelle solution est meilleure (distance plus courte), elle remplace la solution actuelle.

4. **Itération**  
   Ce processus est répété jusqu'à ce qu'aucune amélioration ne soit trouvée, c'est-à-dire que l'algorithme atteigne un minimum local.

### Exemple d'un échange 2-opt

Supposons que le chemin actuel passe par les nœuds A → B → C → D → E.  
Un échange 2-opt entre les arêtes (B → C) et (D → E) inversera l'ordre des nœuds entre ces deux arêtes, donnant le chemin :  
A → B → D → C → E.

Ce simple échange peut réduire la distance totale si les nouvelles arêtes sont plus courtes.

### Avantages

- Simple à implémenter.
- Rapide pour des solutions initiales de petite ou moyenne taille.
- Peut être combiné avec d'autres algorithmes, comme le 3-opt, pour explorer davantage de solutions.

Cependant, l'algorithme 2-opt peut être limité par les minima locaux, ce qui justifie l'utilisation de l'algorithme 3-opt pour une optimisation plus poussée.

## Objectif

L'objectif principal est de trouver une solution optimale ou quasi-optimale en combinant ces deux algorithmes de manière itérative et stratégique.

## Applications

Ce projet peut être utilisé pour résoudre des problèmes d'optimisation dans divers domaines, tels que :
- La logistique (optimisation des itinéraires de livraison)
- La planification (minimisation des coûts de déplacement)
- Les réseaux (optimisation des chemins dans un graphe)

---

Ce projet est une excellente opportunité pour explorer des algorithmes d'optimisation avancés et leur application dans des problèmes réels.