#include <iostream>
#include "instancegenerator.h"
#include "test_multi-opt.h"

using namespace std;

int main() {
    // Demander à l'utilisateur les paramètres pour générer les points
    int numPoints;
    double minCoord, maxCoord;

    cout << "Entrez le nombre de points à générer : ";
    cin >> numPoints;

    cout << "Entrez la coordonnée minimale : ";
    cin >> minCoord;

    cout << "Entrez la coordonnée maximale : ";
    cin >> maxCoord;

    // Générer les points aléatoires
    vector<Point> points = InstanceGenerator::generateRandomPoints(numPoints, minCoord, maxCoord, minCoord, maxCoord);

    // Sauvegarder les points générés dans input.txt
    InstanceGenerator::savePointsToFile(points, "input.txt");
    cout << "Points générés et sauvegardés dans input.txt." << endl;

    // Initialisation du chemin (ordre initial des points)
    vector<int> path(points.size());
    for (size_t i = 0; i < path.size(); ++i) {
        path[i] = static_cast<int>(i);
    }

    // Application de l'algorithme 2-opt
    int depth = 10; // Profondeur maximale
    twoOpt(points, path, depth);

    // Sauvegarde du chemin final dans output.txt
    vector<Point> optimizedPath;
    for (int index : path) {
        optimizedPath.push_back(points[static_cast<size_t>(index)]);
    }
    InstanceGenerator::savePointsToFile(optimizedPath, "output.txt");

    cout << "Chemin optimisé écrit dans output.txt" << endl;
    return 0;
}