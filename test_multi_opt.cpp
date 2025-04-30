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
    if (depth <= 0) return;

    double bestCost = calculateCost(points, path);
    vector<int> bestPath = path;

    for (size_t i = 1; i < path.size() - 1; ++i) {
        for (size_t j = i + 1; j < path.size(); ++j) {
            reverseSegment(path, static_cast<int>(i), static_cast<int>(j));
            double newCost = calculateCost(points, path);
            if (newCost < bestCost) {
                bestCost = newCost;
                bestPath = path;
            }
            reverseSegment(path, static_cast<int>(i), static_cast<int>(j)); // Restaurer le chemin (backtracking)
        }
    }

    path = bestPath;
    twoOpt(points, path, depth - 1);
}
