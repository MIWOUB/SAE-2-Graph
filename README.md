# SAE 2 – Optimisation de Graphe (TSP)

Ce projet implémente un programme d'optimisation basé sur les algorithmes **2-opt** et **3-opt**, utilisés pour résoudre des problèmes d'optimisation combinatoire, comme le célèbre **problème du voyageur de commerce (TSP - Travelling Salesman Problem)**.

### Problème posé  
Dans cette SAE, le problème est le suivant :  
> **190 restaurants** situés dans la **Nièvre** doivent être tous visités une seule fois, en suivant le **chemin le plus court possible**.  
Les restaurants sont représentés par des **nœuds** ayant chacun leurs **coordonnées géographiques**, stockées dans un **fichier texte**.

---

##  Fonctionnement de l’algorithme

1. **Phase 1 – Optimisation 2-opt**  
   Le programme commence par appliquer l’algorithme 2-opt pour améliorer une première solution (généralement aléatoire ou heuristique).

2. **Phase 2 – Optimisation 3-opt**  
   Lorsque 2-opt ne permet plus d’améliorer la solution, le programme utilise l’algorithme 3-opt, plus puissant, pour explorer davantage de combinaisons.

3. **Phase 3 – Retour au 2-opt**  
   Si 3-opt trouve une meilleure solution, une nouvelle phase de 2-opt est lancée pour affiner le chemin obtenu.

---

## Détails de l’algorithme 2-opt

### Principe  
Le 2-opt est un algorithme d'**optimisation locale**. Il améliore le chemin actuel en **échangeant deux arêtes**, si cela réduit la distance totale.

### Étapes :

1. **Initialisation**  
   On part d’une solution initiale reliant tous les nœuds (par exemple un parcours généré aléatoirement).

2. **Recherche d’améliorations**  
   L’algorithme teste toutes les paires d’arêtes possibles. Pour chaque paire, il inverse l’ordre des nœuds entre ces deux arêtes (opération appelée "2-opt swap").

3. **Évaluation**  
   Si ce nouvel agencement réduit la distance totale du parcours, la solution est acceptée.

4. **Itération**  
   Le processus continue jusqu’à ce qu’aucune amélioration ne soit trouvée : un **minimum local** est atteint.

### Exemple d’un échange 2-opt

Supposons un chemin :  
**A → B → C → D → E**  
Un échange entre les arêtes (B → C) et (D → E) donne :  
**A → B → D → C → E**

Cet échange peut réduire la distance totale si les nouvelles connexions sont plus courtes.

### Pseudocode

```
Initialiser improved à vrai
Tant que improved est vrai :
   Mettre improved à faux
   Pour chaque paire d'arêtes (i, j) dans tour :
      Si inverser le segment [i, j] améliore la solution :
         Inverser le segment [i, j]
         Mettre improved à vrai
Retourner le circuit optimisé
```

---

## 🔁 Détails de l’algorithme 3-opt

Le 3-opt est une extension du 2-opt. Il examine **trois arêtes** au lieu de deux, ce qui permet **plus de possibilités d’échange** et d’amélioration.

### Principe :  
À chaque étape, le 3-opt teste plusieurs façons de reconnecter trois segments consécutifs du chemin, et conserve la meilleure configuration.

Cela permet de dépasser certains **minima locaux** que le 2-opt ne peut pas franchir.

---

##  Format des données

Les coordonnées des restaurants sont extraites d’un fichier texte.  
Chaque ligne correspond à un restaurant, par exemple :

```
NomRestaurant1 46.98765 3.12345
NomRestaurant2 47.01234 3.10123
...
```

- La première colonne est le nom.
- La deuxième et troisième colonne sont les **coordonnées GPS** (latitude, longitude).
- Ce fichier est chargé en mémoire pour créer une liste de nœuds avec leur position.

---

##  Avantages des algorithmes

- **2-opt** :
  - Simple à implémenter
  - Rapide pour des graphes de taille moyenne
  - Bonne base d’optimisation locale

- **3-opt** :
  - Meilleure exploration de l’espace des solutions
  - Réduction des risques de rester bloqué dans un minimum local
  - Combine bien avec le 2-opt pour une stratégie efficace

---

##  Objectif du projet

> Trouver une **solution optimale ou quasi-optimale** en combinant les algorithmes 2-opt et 3-opt de manière itérative et intelligente.

---

##  Performances

- Pour 190 restaurants, l’algorithme 2-opt converge généralement en **quelques secondes à quelques minutes** selon la machine.
- Le 3-opt est plus lent mais plus précis.
- Une bonne stratégie alterne les deux pour un compromis entre **temps d’exécution** et **qualité de la solution**.

---

##  Applications

Ce projet a des applications concrètes dans plusieurs domaines :

-  **Logistique** – Optimisation des tournées de livraison
-  **Planification** – Réduction des trajets dans les plannings
-  **Réseaux** – Calculs de plus courts chemins dans des graphes complexes

---

Ce projet est une **excellente opportunité d'apprendre des techniques d’optimisation puissantes**, avec des applications réelles dans l'industrie et la recherche.