# SAE 2 – Optimisation de Graphe (TSP)

Ce projet implémente un programme d'optimisation basé sur l'algorithme **2-opt**, utilisé pour résoudre des problèmes d'optimisation combinatoire, comme le célèbre **problème du voyageur de commerce (TSP - Travelling Salesman Problem)**.

---

## Problème posé

> **Un ensemble de points** doit être visité une seule fois, en suivant le **chemin le plus court possible**.  
> Les points sont représentés par des **nœuds** ayant chacun leurs **coordonnées entières**, générées aléatoirement ou chargées depuis un fichier texte.

---

## Fonctionnement du programme

1. **Génération des points**  
   L'utilisateur peut générer un ensemble de points aléatoires en spécifiant :  
   - Le nombre de points  
   - Les coordonnées minimales et maximales  

   Les points générés sont sauvegardés dans un fichier `input.txt`.

2. **Optimisation avec 2-opt**  
   Le programme applique l'algorithme 2-opt pour optimiser le chemin reliant tous les points.

3. **Sauvegarde du chemin optimisé**  
   Le chemin optimisé est sauvegardé dans un fichier `output.txt`, et la distance totale du chemin est affichée dans la console.

---

## Détails de l’algorithme 2-opt

### Principe

Le 2-opt est un algorithme d'**optimisation locale**. Il améliore le chemin actuel en **échangeant deux arêtes**, si cela réduit la distance totale.

### Étapes

1. **Initialisation**  
   On part d’une solution initiale reliant tous les nœuds dans l'ordre où ils ont été générés.

2. **Recherche d’améliorations**  
   L’algorithme teste toutes les paires d’arêtes possibles. Pour chaque paire, il inverse l’ordre des nœuds entre ces deux arêtes (opération appelée *2-opt swap*).

3. **Évaluation**  
   Si ce nouvel agencement réduit la distance totale du parcours, la solution est acceptée.

4. **Itération**  
   Le processus continue jusqu’à ce qu’aucune amélioration ne soit trouvée : un **minimum local** est atteint.

---

## Format des données

### Fichier `input.txt`

Les points générés ou chargés sont sauvegardés dans un fichier texte au format suivant :

```
1 10 20
2 15 25
3 30 35
...
```

- La première colonne est l'**identifiant** du point.  
- Les deuxième et troisième colonnes sont les **coordonnées entières** du point (`x` et `y`).

### Fichier `output.txt`

Le chemin optimisé est sauvegardé dans un fichier texte au même format que `input.txt`, mais dans l'ordre des points optimisé par l'algorithme 2-opt.

---

## Exemple d'exécution

### Entrée utilisateur

```
Entrez le nombre de points à générer : 5
Entrez la coordonnée minimale : 0
Entrez la coordonnée maximale : 10
```

### Fichier `input.txt` généré

```
1 2 3
2 5 7
3 8 1
4 4 6
5 9 9
```

### Sortie dans la console

```
Points générés et sauvegardés dans input.txt.
Distance totale du chemin optimisé : 25.6789
Chemin optimisé écrit dans output.txt
```

### Fichier `output.txt` généré

```
1 2 3
3 8 1
5 9 9
4 4 6
2 5 7
```

---

## Avantages de l’algorithme 2-opt

- **Simple à implémenter** : L'algorithme est facile à coder et à comprendre.  
- **Rapide** : Convient pour des graphes de taille moyenne.  
- **Efficace** : Fournit une solution proche de l'optimum global pour de nombreux cas.

---

## Objectif du projet

> Trouver une **solution optimisée** pour le problème du voyageur de commerce en utilisant l'algorithme 2-opt.

---


---

## Instructions pour utiliser le programme

1. **Compiler le programme** :

   ```bash
   g++ -o main main.cpp test_multi_opt.cpp instancegenerator.cpp
   ```

2. **Exécuter le programme** :

   ```bash
   ./main
   ```
