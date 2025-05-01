#ifndef INSTANCEGENERATOR_H
#define INSTANCEGENERATOR_H

#include <vector>
#include <string>

// Structure pour représenter un point
struct Point {
    int id;     // Identifiant unique du point
    int x, y;   // Coordonnées en entiers
};

// Classe pour générer des instances de graphes
class InstanceGenerator {
public:
    // Génère un ensemble de points aléatoires
    static std::vector<Point> generateRandomPoints(int numPoints, int minX, int maxX, int minY, int maxY);

    // Sauvegarde les points dans un fichier
    static void savePointsToFile(const std::vector<Point>& points, const std::string& filename);

    // Charge les points depuis un fichier
    static std::vector<Point> loadPointsFromFile(const std::string& filename);
};

// Fonctions utilitaires
double calculateDistance(const Point& a, const Point& b); // Calcul de la distance entre deux points
void calculateDistanceMatrix(const std::vector<Point>& points); // Affiche la matrice des distances
void copyFile(const std::string& source, const std::string& destination); // Copie un fichier

#endif // INSTANCEGENERATOR_H