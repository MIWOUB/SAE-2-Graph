#ifndef TEST_MULTI_OPT_H
#define TEST_MULTI_OPT_H

#include <vector>
#include "instancegenerator.h"

// Fonction pour calculer la distance entre deux points
double distance(const Point& a, const Point& b);

// Fonction pour calculer le coût total d'un chemin
double calculateCost(const std::vector<Point>& points, const std::vector<int>& path);

// Fonction pour inverser un segment du chemin
void reverseSegment(std::vector<int>& path, int start, int end);

// Algorithme 2-opt
void twoOpt(std::vector<Point>& points, std::vector<int>& path, int depth);

#endif // TEST_MULTI_OPT_H