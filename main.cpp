#include <iostream>
#include <locale>
#include <codecvt>
#include <windows.h> // Nécessaire pour SetConsoleOutputCP et SetConsoleCP
#include "instancegenerator.h"
#include "test_multi-opt.h"
#include <fstream> // Pour copier les fichiers
#include <chrono> // Pour mesurer le temps

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

    // Mesurer le temps total pour trouver le meilleur chemin
    auto totalStart = chrono::high_resolution_clock::now();

    // Demander à l'utilisateur la profondeur pour le 2-opt
    int depth;
    cout << "Entrez la profondeur maximale pour le 2-opt : ";
    cin >> depth;

    // Application initiale de l'algorithme 2-opt
    auto twoOptStart = chrono::high_resolution_clock::now();
    twoOpt(points, path, depth);
    auto twoOptEnd = chrono::high_resolution_clock::now();

    // Calculer le temps pris par le 2-opt
    auto twoOptDuration = chrono::duration_cast<chrono::milliseconds>(twoOptEnd - twoOptStart).count();
    cout << "Temps pris par le 2-opt initial : " << twoOptDuration << " ms" << endl;

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

    // Initialiser un compteur pour le nombre d'exécutions de l'algorithme 2-opt
    int executionCount = 0;

    // Boucle pour exécuter le 2-opt jusqu'à ce qu'il n'y ait plus d'amélioration
    while (true) {
        // Incrémenter le compteur à chaque exécution
        executionCount++;

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
        twoOptStart = chrono::high_resolution_clock::now();
        twoOpt(points, path, depth);
        twoOptEnd = chrono::high_resolution_clock::now();

        // Calculer le temps pris par le 2-opt
        twoOptDuration = chrono::duration_cast<chrono::milliseconds>(twoOptEnd - twoOptStart).count();
        cout << "Temps pris par le 2-opt : " << twoOptDuration << " ms" << endl;

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

    // Calculer le temps total pour trouver le meilleur chemin
    auto totalEnd = chrono::high_resolution_clock::now();
    auto totalDuration = chrono::duration_cast<chrono::milliseconds>(totalEnd - totalStart).count();
    cout << "Temps total pour trouver le meilleur chemin : " << totalDuration / 1000.0 << " secondes" << endl;

    // Afficher le nombre total d'exécutions de l'algorithme 2-opt
    cout << "Nombre total d'exécutions de l'algorithme 2-opt : " << executionCount << endl;

    return 0;
}