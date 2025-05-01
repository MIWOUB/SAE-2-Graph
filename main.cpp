#include <iostream>
#include <locale>
#include <codecvt>
#include <windows.h> // Nécessaire pour SetConsoleOutputCP et SetConsoleCP
#include "instancegenerator.h"
#include "test_multi-opt.h"
#include <fstream> // Pour copier les fichiers

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

    // Demander à l'utilisateur la profondeur pour le 2-opt
    int depth;
    cout << "Entrez la profondeur maximale pour le 2-opt : ";
    cin >> depth;

    // Application initiale de l'algorithme 2-opt
    twoOpt(points, path, depth);

    // Calcul de la distance totale du chemin optimisé
    double initialDistance = calculateCost(points, path);
    double previousDistance = initialDistance;
    cout << "Distance totale du chemin initial : " << initialDistance << endl;

    // Sauvegarde du chemin final dans output.txt
    vector<Point> optimizedPath;
    for (int index : path) {
        optimizedPath.push_back(points[static_cast<size_t>(index)]);
    }
    InstanceGenerator::savePointsToFile(optimizedPath, "output.txt");

    cout << "Chemin optimisé écrit dans output.txt" << endl;

    // Boucle pour exécuter le 2-opt jusqu'à ce qu'il n'y ait plus d'amélioration
    while (true) {
        // Copier output.txt dans input.txt
        copyFile("output.txt", "input.txt");

        // Recharger les points depuis input.txt
        points = InstanceGenerator::loadPointsFromFile("input.txt");

        // Réinitialiser le chemin
        path.resize(points.size());
        for (size_t i = 0; i < path.size(); ++i) {
            path[i] = static_cast<int>(i);
        }

        // Réappliquer le 2-opt
        twoOpt(points, path, depth);

        // Calculer la nouvelle distance
        double newDistance = calculateCost(points, path);
        cout << "Nouvelle distance totale du chemin optimisé : " << newDistance << endl;

        // Comparer avec la distance précédente
        if (newDistance >= previousDistance) {
            cout << "Le chemin n'a pas été amélioré davantage." << endl;
            cout << "Distance initiale du tout premier chemin : " << initialDistance << endl;
            cout << "Distance finale du chemin jugé optimal : " << newDistance << endl;
            break;
        }

        // Mettre à jour la distance précédente
        previousDistance = newDistance;

        // Sauvegarder le nouveau chemin dans output.txt
        optimizedPath.clear();
        for (int index : path) {
            optimizedPath.push_back(points[static_cast<size_t>(index)]);
        }
        InstanceGenerator::savePointsToFile(optimizedPath, "output.txt");

        cout << "Chemin optimisé écrit dans output.txt" << endl;
    }

    return 0;
}