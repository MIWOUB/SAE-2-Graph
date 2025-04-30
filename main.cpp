#include <iostream>
#include <locale>
#include <codecvt>
#include <windows.h> // Nécessaire pour SetConsoleOutputCP et SetConsoleCP
#include "instancegenerator.h"
#include "test_multi-opt.h"

using namespace std;

int main() {
    // Configurer la console pour utiliser UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    cout.imbue(locale("")); // Utiliser la locale par défaut pour gérer les caractères spéciaux

    // Demander à l'utilisateur les paramètres pour générer les points
    int numPoints;
    int minCoord, maxCoord;

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

    // Calcul de la distance totale du chemin optimisé
    double totalDistance = calculateCost(points, path);
    cout << "Distance totale du chemin optimisé : " << totalDistance << endl;

    // Sauvegarde du chemin final dans output.txt
    vector<Point> optimizedPath;
    for (int index : path) {
        optimizedPath.push_back(points[static_cast<size_t>(index)]);
    }
    InstanceGenerator::savePointsToFile(optimizedPath, "output.txt");

    cout << "Chemin optimisé écrit dans output.txt" << endl;
    return 0;
}