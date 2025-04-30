#include <iostream>
#include "instancegenerator.h"
#include "test_multi-opt.h"

using namespace std;

int main() {
    // Chargement des points depuis le fichier input.txt
    vector<Point> points = InstanceGenerator::loadPointsFromFile("input.txt");

    if (points.empty()) {
        cerr << "Erreur : aucune coordonnée trouvée dans input.txt. Vérifiez que le fichier contient des points valides." << endl;
        return 1;
    }

    cout << "Points chargés depuis input.txt : " << points.size() << " points." << endl;

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