#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
#include "instancegenerator.h"

using namespace std;

// Fonction pour calculer la distance entre deux points
double distance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Fonction pour calculer le coût total d'un chemin
double calculateCost(const vector<Point>& points, const vector<int>& path) {
    double cost = 0.0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        cost += distance(points[static_cast<size_t>(path[i])], points[static_cast<size_t>(path[i + 1])]);
    }
    cost += distance(points[static_cast<size_t>(path.back())], points[static_cast<size_t>(path[0])]); // Retour au point de départ
    return cost;
}

// Fonction pour inverser un segment du chemin
void reverseSegment(vector<int>& path, int start, int end) {
    while (start < end) {
        swap(path[static_cast<size_t>(start)], path[static_cast<size_t>(end)]);
        ++start;
        --end;
    }
}

// Algorithme 2-opt
void twoOpt(vector<Point>& points, vector<int>& path, int depth) {
    // Arrêt récursif si la profondeur est atteinte
    if (depth <= 0) return;

    // Calcul du coût du chemin actuel
    double bestCost = calculateCost(points, path);
    // Sauvegarde du meilleur chemin trouvé à cette itération
    vector<int> bestPath = path;

    // Parcours de toutes les paires d'indices pour inverser les segments
    for (size_t i = 1; i < path.size() - 1; ++i) {
        for (size_t j = i + 1; j < path.size(); ++j) {
            // Inverser le segment entre i et j
            reverseSegment(path, static_cast<int>(i), static_cast<int>(j));
            // Calculer le coût du nouveau chemin
            double newCost = calculateCost(points, path);
            // Si le nouveau chemin est meilleur, on le garde
            if (newCost < bestCost) {
                bestCost = newCost;
                bestPath = path;
            }
            // Restaurer le chemin d'origine (backtracking)
            reverseSegment(path, static_cast<int>(i), static_cast<int>(j));
        }
    }

    // Mettre à jour le chemin avec le meilleur trouvé à cette itération
    path = bestPath;
    // Appel récursif pour continuer l'amélioration jusqu'à la profondeur donnée
    twoOpt(points, path, depth - 1);
}
