#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Pour std::find_if
#include "instancegenerator.h"
#include <sstream>

using namespace std;

// Fonction pour vérifier si un point existe déjà dans le vecteur
bool pointExists(const vector<Point>& points, const Point& p) {
    return find_if(points.begin(), points.end(), [&p](const Point& existingPoint) {
        return existingPoint.x == p.x && existingPoint.y == p.y;
    }) != points.end();
}

// Fonction pour générer des coordonnées aléatoires dans un intervalle donné
vector<Point> generatePoints(int numPoints, int minCoord, int maxCoord) {
    vector<Point> points;
    int idCounter = 1; // Compteur pour les identifiants uniques

    while (points.size() < numPoints) {
        int x = static_cast<int>(minCoord + rand() % (maxCoord - minCoord + 1));
        int y = static_cast<int>(minCoord + rand() % (maxCoord - minCoord + 1));
        Point newPoint = {idCounter, x, y};

        // Vérifier si le point existe déjà
        if (!pointExists(points, newPoint)) {
            points.push_back(newPoint);
            ++idCounter; // Incrémenter l'identifiant pour le prochain point
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
        file << point.id << " " << point.x << " " << point.y << endl;
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

std::vector<Point> InstanceGenerator::loadPointsFromFile(const std::string& filename) {
    std::vector<Point> points;
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Erreur : impossible d'ouvrir le fichier " << filename << std::endl;
        return points;
    }

    int id, x, y;
    while (inputFile >> id >> x >> y) {
        points.push_back({id, x, y});
    }
    inputFile.close();
    return points;
}

void InstanceGenerator::savePointsToFile(const std::vector<Point>& points, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        std::cerr << "Erreur : impossible de créer le fichier " << filename << std::endl;
        return;
    }

    for (const auto& point : points) {
        outputFile << point.id << " " << point.x << " " << point.y << std::endl;
    }
    outputFile.close();
}

std::vector<Point> InstanceGenerator::generateRandomPoints(int numPoints, int minX, int maxX, int minY, int maxY) {
    std::vector<Point> points;
    int idCounter = 1; // Identifiant unique pour chaque point

    for (int i = 0; i < numPoints; ++i) {
        int x = minX + rand() % (maxX - minX + 1);
        int y = minY + rand() % (maxY - minY + 1);
        points.push_back({idCounter++, x, y});
    }

    return points;
}

void copyFile(const string& source, const string& destination) {
    ifstream src(source, ios::binary);
    ofstream dest(destination, ios::binary);
    dest << src.rdbuf();
}
