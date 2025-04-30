#include <iostream>
#include <vector>
#include <tuple>
#include <limits>
#include <queue>
#include <functional>
#include <algorithm>
#include <utility>
#include <chrono>
#include <fstream>
#include <cmath> // Pour calculer les distances
#include <iomanip> // Pour formater les sorties numériques

using namespace std;

// Structure pour représenter un point avec des coordonnées
struct Point {
    int x, y;
};

// Structure pour représenter une arête dans le graphe
struct Edge {
    int src, dest;
    double weight; // Poids de l'arête (distance entre deux points)
};

// Classe pour représenter un graphe
class Graph {
public:
    int V;                           // Nombre de sommets
    vector<vector<pair<int, double>>> adj; // Liste d'adjacence avec les poids
    vector<Edge> edges;              // Liste des arêtes

    // Constructeur pour initialiser le graphe avec V sommets
    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    // Fonction pour ajouter une arête au graphe
    void addEdge(int u, int v, double w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); // Graphe non orienté
        edges.push_back({u, v, w});
    }

    // Fonction pour afficher la liste d'adjacence du graphe
    void printGraph() {
        cout << "Liste d'adjacence du graphe :" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (const auto& edge : adj[i]) { // Utilisation de `const auto&` pour éviter les copies inutiles
                cout << "(" << edge.first << ", " << fixed << setprecision(2) << edge.second << ") ";
            }
            cout << endl;
        }
    }
};

// Fonction pour lire les points depuis le fichier input.txt
vector<Point> readPointsFromFile(const string& filename) {
    vector<Point> points;
    ifstream file(filename);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << endl;
        return points;
    }

    int x, y;
    while (file >> x >> y) {
        points.push_back({x, y});
    }
    file.close();
    return points;
}

// Fonction pour calculer la distance entre deux points
double calculateDistance(const Point& a, const Point& b) {
    return sqrt(static_cast<double>((a.x - b.x) * (a.x - b.x)) + 
                static_cast<double>((a.y - b.y) * (a.y - b.y)));
}

// Fonction pour construire un graphe complet à partir des points
Graph buildGraphFromPoints(const vector<Point>& points) {
    int n = points.size();
    Graph G(n);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double dist = calculateDistance(points[i], points[j]);
            G.addEdge(i, j, dist);
        }
    }
    return G;
}

// Fonction pour alterner le 2-opt et le 3-opt
void two_three_opt(Graph& G, vector<int>& tour) {
    bool improved = true;

    while (improved) {
        improved = false;

        // Exécuter le 2-opt
        bool two_opt_improved = true;
        while (two_opt_improved) {
            two_opt_improved = false;

            int n = tour.size();
            for (int i = 1; i < n - 1; i++) {
                for (int j = i + 1; j < n; j++) {
                    if (j == n - 1 && i == 1)
                        continue;

                    double gain = G.adj[tour[i - 1]][0].second + G.adj[tour[j]][0].second
                                - G.adj[tour[i - 1]][0].second - G.adj[tour[i]][0].second;

                    if (gain > 0) {
                        reverse(tour.begin() + i, tour.begin() + j + 1);
                        two_opt_improved = true;
                        improved = true;
                    }
                }
            }
        }
    }
}

int main() {
    // Lire les points depuis le fichier input.txt
    vector<Point> points = readPointsFromFile("input.txt");
    if (points.empty()) {
        cerr << "Erreur : Aucun point n'a été lu depuis le fichier." << endl;
        return 1;
    }

    // Construire le graphe à partir des points
    Graph G = buildGraphFromPoints(points);

    // Afficher le graphe
    G.printGraph();

    // Initialiser un tour initial (cycle)
    vector<int> tour(points.size());
    for (int i = 0; i < points.size(); i++) {
        tour[i] = i;
    }
    tour.push_back(0); // Retour au point de départ

    // Afficher le tour initial
    cout << "Tour initial : ";
    for (int node : tour)
        cout << node << " ";
    cout << endl;

    // Mesurer le temps d'exécution
    auto start = chrono::high_resolution_clock::now();

    // Appliquer l'algorithme 2-opt
    two_three_opt(G, tour);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    // Afficher le tour optimisé
    cout << "Tour optimisé : ";
    for (int node : tour)
        cout << node << " ";
    cout << endl;

    // Afficher le temps d'exécution
    cout << "Temps d'exécution : " << duration.count() << " ms" << endl;

    return 0;
}