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