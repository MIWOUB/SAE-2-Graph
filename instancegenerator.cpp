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

// Fonction pour verifier si un point existe dejà dans le vecteur
bool pointExists(const vector<Point>& points, const Point& p) {
    return find_if(points.begin(), points.end(), [&p](const Point& existingPoint) {
        return existingPoint.x == p.x && existingPoint.y == p.y;
    }) != points.end();
}

// Fonction pour generer des coordonnees aleatoires dans un intervalle donne
vector<Point> generatePoints(int numPoints, int minCoord, int maxCoord) {
    vector<Point> points;
    while (points.size() < numPoints) {
        int x = minCoord + rand() % (maxCoord - minCoord + 1);
        int y = minCoord + rand() % (maxCoord - minCoord + 1);
        Point newPoint = {x, y};

        // Verifier si le point existe dejà
        if (!pointExists(points, newPoint)) {
            points.push_back(newPoint);
        }
    }
    return points;
}

// Fonction pour ecrire les points dans un fichier
void writePointsToFile(const vector<Point>& points, const string& filename) {
    ofstream file(filename);
    if (!file) {
        cerr << "Erreur : Impossible de creer le fichier " << filename << endl;
        return;
    }
    for (const auto& point : points) {
        file << point.x << " " << point.y << endl;
    }
    file.close();
    cout << "Fichier " << filename << " cree avec succès." << endl;
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
    srand(static_cast<unsigned>(time(0))); // Initialiser le generateur de nombres aleatoires

    int numPoints, minCoord, maxCoord;
    cout << "Entrez le nombre de sommets : ";
    cin >> numPoints;
    cout << "Entrez la coordonnee minimale : ";
    cin >> minCoord;
    cout << "Entrez la coordonnee maximale : ";
    cin >> maxCoord;

    // Generer les points
    vector<Point> points = generatePoints(numPoints, minCoord, maxCoord);

    // ecrire les points dans le fichier input.txt
    writePointsToFile(points, "input.txt");

    // Calculer et afficher la matrice des distances
    calculateDistanceMatrix(points);

    return 0;
}