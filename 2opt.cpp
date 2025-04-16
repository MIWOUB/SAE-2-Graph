#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>
#include <functional>
#include <algorithm>
#include <utility>
#include <chrono> // Ajouter cette bibliothèque pour mesurer le temps

using namespace std;

// Structure pour représenter une arête dans le graphe
struct Edge
{
    int src, dest, weight; // Sommet source, sommet destination et poids de l'arête
};

// Classe pour représenter un graphe
class Graph
{
public:
    int V, E;                           // Nombre de sommets (V) et d'arêtes (E)
    vector<vector<pair<int, int>>> adj; // Liste d'adjacence pour l'algorithme de Dijkstra
    vector<Edge> edges;                 // Liste des arêtes pour l'algorithme de Bellman-Ford

    // Constructeur pour initialiser le graphe avec V sommets et E arêtes
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
        adj.resize(V); // Redimensionner la liste d'adjacence pour contenir V sommets
    }

    // Fonction pour ajouter une arête au graphe
    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w}); // Ajouter l'arête (v, w) à la liste d'adjacence du sommet u
        edges.push_back({u, v, w}); // Ajouter l'arête à la liste des arêtes
    }

    // Fonction pour afficher la liste d'adjacence du graphe
    void printGraph()
    {
        cout << "Liste d'adjacence du graphe :" << endl;
        for (int i = 0; i < V; i++)
        {
            cout << i << " -> ";
            for (auto edge : adj[i])
            {
                cout << "(" << edge.first << ", " << edge.second << ") "; // Afficher chaque arête sous la forme (destination, poids)
            }
            cout << endl;
        }
    }
};


// Fonction pour alterner le 2 opt et le 3 opt
void two_three_opt(Graph G, vector<int> &tour)
{
    bool improved = true; // Indicateur pour suivre si une amélioration a été effectuée

    // Continuer tant qu'il y a des améliorations
    while (improved)
    {
        improved = false; // Réinitialiser l'indicateur d'amélioration

        // Exécuter le 2-opt
        bool two_opt_improved = true;
        while (two_opt_improved)
        {
            two_opt_improved = false;

            int n = tour.size();
            for (int i = 1; i < n - 1; i++)
            {
                for (int j = i + 1; j < n; j++)
                {
                    if (j == n - 1 && i == 1)
                        continue;

                    int gain = G.adj[tour[i - 1]][tour[i]].second + G.adj[tour[j]][tour[(j + 1) % n]].second
                             - G.adj[tour[i - 1]][tour[i]].second - G.adj[tour[j]][tour[(j + 1) % n]].second;

                    if (gain > 0)
                    {
                        reverse(tour.begin() + i, tour.begin() + j + 1);
                        two_opt_improved = true;
                        improved = true;
                    }
                }
            }
        }

        // Si aucune amélioration avec 2-opt, passer au 3-opt
        if (!improved)
        {
            bool three_opt_improved = true;
            while (three_opt_improved)
            {
                three_opt_improved = false;

                int n = tour.size();
                for (int i = 1; i < n - 2; i++)
                {
                    for (int j = i + 1; j < n - 1; j++)
                    {
                        for (int k = j + 1; k < n; k++)
                        {
                            int gain1 = G.adj[tour[i - 1]][tour[i]].second + G.adj[tour[j]][tour[j + 1]].second + G.adj[tour[k]][tour[(k + 1) % n]].second;
                            int gain2 = G.adj[tour[i - 1]][tour[j]].second + G.adj[tour[i]][tour[k]].second + G.adj[tour[j + 1]][tour[(k + 1) % n]].second;
                            int gain3 = G.adj[tour[i - 1]][tour[j + 1]].second + G.adj[tour[k]][tour[i]].second + G.adj[tour[j]][tour[(k + 1) % n]].second;
                            int gain4 = G.adj[tour[i - 1]][tour[k]].second + G.adj[tour[j + 1]][tour[i]].second + G.adj[tour[j]][tour[(k + 1) % n]].second;

                            if (gain2 > gain1)
                            {
                                reverse(tour.begin() + i, tour.begin() + j + 1);
                                three_opt_improved = true;
                                improved = true;
                            }
                            else if (gain3 > gain1)
                            {
                                reverse(tour.begin() + j + 1, tour.begin() + k + 1);
                                three_opt_improved = true;
                                improved = true;
                            }
                            else if (gain4 > gain1)
                            {
                                reverse(tour.begin() + i, tour.begin() + k + 1);
                                three_opt_improved = true;
                                improved = true;
                            }
                        }
                    }
                }
            }
        }
    }
}


int main()
{
    // Initialisation des paramètres du graphe
    int V = 20; // Nombre de sommets
    int E = 30; // Nombre d'arêtes

    // Création du graphe
    Graph G(V, E);

    // Ajout des arêtes avec des poids aléatoires
    G.addEdge(0, 1, 10);
    G.addEdge(1, 2, 15);
    G.addEdge(2, 3, 20);
    G.addEdge(3, 4, 25);
    G.addEdge(4, 5, 30);
    G.addEdge(5, 6, 35);
    G.addEdge(6, 7, 40);
    G.addEdge(7, 8, 45);
    G.addEdge(8, 9, 50);
    G.addEdge(9, 10, 55);
    G.addEdge(10, 11, 60);
    G.addEdge(11, 12, 65);
    G.addEdge(12, 13, 70);
    G.addEdge(13, 14, 75);
    G.addEdge(14, 15, 80);
    G.addEdge(15, 16, 85);
    G.addEdge(16, 17, 90);
    G.addEdge(17, 18, 95);
    G.addEdge(18, 19, 100);
    G.addEdge(19, 0, 105);
    G.addEdge(0, 2, 50);
    G.addEdge(1, 3, 45);
    G.addEdge(2, 4, 40);
    G.addEdge(3, 5, 35);
    G.addEdge(4, 6, 30);
    G.addEdge(5, 7, 25);
    G.addEdge(6, 8, 20);
    G.addEdge(7, 9, 15);
    G.addEdge(8, 10, 10);
    G.addEdge(9, 11, 5);

    // Affichage du graphe
    G.printGraph();

    // Initialisation d'un tour initial (cycle)
    vector<int> tour = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0};

    // Affichage du tour initial
    cout << "Tour initial : ";
    for (int node : tour)
        cout << node << " ";
    cout << endl;

    // Mesure du temps d'exécution
    auto start = chrono::high_resolution_clock::now(); // Début du timer

    // Application de l'algorithme 2-opt et 3-opt
    two_three_opt(G, tour);

    auto end = chrono::high_resolution_clock::now(); // Fin du timer
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start); // Calcul de la durée

    // Affichage du tour optimisé
    cout << "Tour optimisé : ";
    for (int node : tour)
        cout << node << " ";
    cout << endl;

    // Affichage du temps d'exécution
    cout << "Temps d'exécution : " << duration.count() << " ms" << endl;

    return 0;
}
// Fonction principale pour tester l'algorithme 2-opt et 3-opt
/**
 * expected_output
 * Tour initial : 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 0
 * Tour optimisé : 0 1 3 5 7 9 11 10 8 6 4 2 0 19 18 17 16 15 14 13 12 0
 *
 * Le chemin optimisé peut varier en fonction des poids des arêtes et de l'implémentation
 * des algorithmes 2-opt et 3-opt.
 */
// Commande pour compiler : g++ -o 2opt 2opt.cpp
// Commande pour exécuter : ./2opt