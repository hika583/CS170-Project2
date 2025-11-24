#ifndef FEATURE_SELECTION_H
#define FEATURE_SELECTION_H

#include <vector>
#include <string>

using namespace std;

// Stub evaluation function (Part I): returns random "accuracy" 0–100
double evaluateFeatureSet(const vector<int>& features);

// Utility to print feature sets like {1,2,4}
string featureSetToString(const vector<int>& features);

// Forward Selection search
void forwardSelection(int totalFeatures);

// Backward Elimination search
void backwardElimination(int totalFeatures);

#endif // FEATURE_SELECTION_H