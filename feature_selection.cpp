// feature_selection.cpp
#include "feature_selection.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>

using namespace std;


// --------- Helper Functions ---------

// Stub evaluation function (Part I): returns random "accuracy" 0–100
double evaluateFeatureSet(const vector<int>& features) {
    // mix random generator with time to get different results each run
    static mt19937 rng(static_cast<unsigned int>(time(nullptr))); 
    // uniform distribution between 0 and 100 using dist
    static uniform_real_distribution<double> dist(0.0, 100.0);
    // silence unused warning (we don't use features in Part I)
    (void)features;
    // return random accuracy using dist and rng
    return dist(rng);
}

string featureSetToString(const vector<int>& features) {
    string s = "{";
    for (size_t i = 0; i < features.size(); ++i) {
        s += to_string(features[i]);
        if (i + 1 < features.size()) s += ",";
    }
    s += "}";
    return s;
}


/*
--------- Forward Selection ---------

Forward Selection is a greedy feature selection algorithm that begins with 
an empty feature set and adds features one at a time. At each step, the algorithm 
evaluates every unused feature by temporarily adding it to the current set and 
computing the evaluation accuracy. It selects the feature whose addition results 
in the highest accuracy and permanently adds it to the set. 

This function maintains a list of "remaining features" and removes 
each selected feature from that list as the search progresses.

*/

void forwardSelection(int totalFeatures) {
    cout << "Using no features and \"random\" evaluation, I get an accuracy of "
         << evaluateFeatureSet({}) << "%\n\n";
    cout << "Beginning search.\n\n";

    vector<int> currentSetOfFeatures;
    double bestOverallAccuracy = 0.0;
    vector<int> bestOverallSet;

    // Build list of remaining features to test
    vector<int> remainingFeatures;
    for (int i = 1; i <= totalFeatures; ++i) {
        remainingFeatures.push_back(i);
    }

    // Loop once per level (max totalFeatures levels)
    for (int level = 1; level <= totalFeatures; ++level) {

        if (remainingFeatures.empty()) break;

        int bestIndexThisLevel = -1;    // index inside remainingFeatures
        double bestAccuracyThisLevel = -1.0;

        // Try adding each remaining feature
        for (int i = 0; i < (int)remainingFeatures.size(); ++i) {

            int f = remainingFeatures[i];

            vector<int> candidateSet = currentSetOfFeatures;
            candidateSet.push_back(f);

            double accuracy = evaluateFeatureSet(candidateSet);
            cout << "\tUsing feature(s) " 
                 << featureSetToString(candidateSet)
                 << " accuracy is " << accuracy << "%\n";

            if (accuracy > bestAccuracyThisLevel) {
                bestAccuracyThisLevel = accuracy;
                bestIndexThisLevel = i;
            }
        }

        cout << "\n";

        if (bestIndexThisLevel == -1) break;

        // Add the best feature from this level
        int featureToAdd = remainingFeatures[bestIndexThisLevel];
        currentSetOfFeatures.push_back(featureToAdd);

        // Remove chosen feature from remaining
        remainingFeatures.erase(remainingFeatures.begin() + bestIndexThisLevel);

        cout << "Feature set " << featureSetToString(currentSetOfFeatures)
             << " was best, accuracy is " << bestAccuracyThisLevel << "%\n\n";

        // Warning if accuracy falls
        if (bestAccuracyThisLevel < bestOverallAccuracy) {
            cout << "(Warning, Accuracy has decreased!)\n";
        }

        // Track global best
        if (bestAccuracyThisLevel > bestOverallAccuracy) {
            bestOverallAccuracy = bestAccuracyThisLevel;
            bestOverallSet = currentSetOfFeatures;
        }
    }

    cout << "\nFinished search!! The best feature subset is "
         << featureSetToString(bestOverallSet)
         << ", which has an accuracy of " << bestOverallAccuracy << "%\n\n";
}



// --------- Backward Elimination ---------
void backwardElimination(int totalFeatures) {
    // REMOVE WHEN CODING/IMPLEMENTING THIS FUNCTION
    (void)  totalFeatures; // to shush the error that its not being used
}
