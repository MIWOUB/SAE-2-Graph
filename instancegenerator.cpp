#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Pour std::find_if

using namespace std;

struct Point {
    int x, y;
};

// Fonction pour vérifier si un point existe déjà dans le vecteur
bool pointExists(const vector<Point>& points, const Point& p) {
    return find_if(points.begin(), points.end(), [&p](const Point& existingPoint) {
        return existingPoint.x == p.x && existingPoint.y == p.y;
    }) != points.end();
}

// Fonction pour générer des coordonnées aléatoires dans un intervalle donné
vector<Point> generatePoints(int numPoints, int minCoord, int maxCoord) {
    vector<Point> points;
    while (points.size() < numPoints) {
        int x = minCoord + rand() % (maxCoord - minCoord + 1);
        int y = minCoord + rand() % (maxCoord - minCoord + 1);
        Point newPoint = {x, y};

        // Vérifier si le point existe déjà
        if (!pointExists(points, newPoint)) {
            points.push_back(newPoint);
        }
    }
    return points;
}

// Fonction pour écrire les points dans un fichier
void writePointsToFile(const vector<Point>& points, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Erreur : Impossible de créer le fichier " << filename << endl;
        return;
    }
    for (const auto& point : points) {
        file << point.x << " " << point.y << endl;
    }
    file.close();
    cout << "Fichier " << filename << " créé avec succès." << endl;
}

// Fonction pour calculer la distance entre deux points
double calculateDistance(const Point& a, const Point& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Fonction pour calculer et afficher la matrice des distances
void calculateDistanceMatrix(const vector<Point>& points) {
    int n = points.size();
    cout << "Matrice des distances :" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << calculateDistance(points[i], points[j]) << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(static_cast<unsigned>(time(0))); // Initialiser le générateur de nombres aléatoires

    int numPoints, minCoord, maxCoord;
    cout << "Entrez le nombre de sommets : ";
    cin >> numPoints;
    cout << "Entrez la coordonnée minimale : ";
    cin >> minCoord;
    cout << "Entrez la coordonnée maximale : ";
    cin >> maxCoord;

    // Générer les points
    vector<Point> points = generatePoints(numPoints, minCoord, maxCoord);

    // Écrire les points dans le fichier input.txt
    writePointsToFile(points, "input.txt");

    // Calculer et afficher la matrice des distances
    calculateDistanceMatrix(points);

    return 0;
}