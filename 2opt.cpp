#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>
#include <functional>
#include <algorithm>
#include <utility>

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

// Fonction pour exécuter l'algorithme 2-opt afin d'optimiser un circuit donné
void two_opt(Graph G, vector<int> &tour)
{
    int n = tour.size(); // Nombre de sommets dans le circuit
    bool improved = true; // Indicateur pour suivre si une amélioration a été effectuée

    // Continuer à optimiser le circuit tant qu'il est possible d'améliorer
    while (improved)
    {
        improved = false; // Réinitialiser l'indicateur d'amélioration

        // Parcourir toutes les paires d'arêtes dans le circuit
        for (int i = 1; i < n - 1; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                // Ignorer le cas où inverser le segment reviendrait à inverser tout le circuit
                if (j == n - 1 && i == 1)
                    continue;

                // Calculer le gain obtenu en inversant le segment [i, j]
                int gain = G.adj[tour[i - 1]][tour[i]].second + G.adj[tour[j]][tour[(j + 1) % n]].second
                         - G.adj[tour[i - 1]][tour[i]].second - G.adj[tour[j]][tour[(j + 1) % n]].second;

                // Si le gain est positif, inverser le segment pour améliorer le circuit
                if (gain > 0)
                {
                    reverse(tour.begin() + i, tour.begin() + j + 1); // Inverser le segment [i, j]
                    improved = true; // Marquer qu'une amélioration a été effectuée
                }
            }
        }
    }
}