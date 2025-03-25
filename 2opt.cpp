#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>
#include <functional>
#include <algorithm>
#include <utility>

using namespace std;
struct Edge
{
    int src, dest, weight;
};

class Graph
{
public:
    int V, E;                           // Nombre de sommets (V) et d'arêtes (E)
    vector<vector<pair<int, int>>> adj; // Liste d'adjacence pour Dijkstra
    vector<Edge> edges;                 // Liste d'arêtes pour Bellman-Ford

    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w)
    {
        adj[u].push_back({v, w});
        edges.push_back({u, v, w});
    }

    void printGraph()
    {
        cout << "Liste d'adjacence du graphe :" << endl;
        for (int i = 0; i < V; i++)
        {
            cout << i << " -> ";
            for (auto edge : adj[i])
            {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }
};

void two_opt(Graph G, vector<int> &tour)
{

}