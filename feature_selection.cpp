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

/*Starts with all features and removes one at a time.
   At each step, try removing each feature, evaluate the accuracy,
   and permanently remove the feature whose removal gives the best accuracy. */

void backwardElimination(int totalFeatures) {
    // Start with all features
    vector<int> currentSetOfFeatures;
    for(int i=1; i <=totalFeatures; ++i){
        currentSetOfFeatures.push_back(i);
    }

     if (currentSetOfFeatures.empty()) {
        cout << "No features to run backward elimination on.\n\n";
        return;
    }
     // Evaluate using all features first
    double currentAccuracy = evaluateFeatureSet(currentSetOfFeatures);
    double bestOverallAccuracy = currentAccuracy;
    vector<int> bestOverallSet = currentSetOfFeatures;

    cout << "Using all features "
         << featureSetToString(currentSetOfFeatures)
         << " and \"random\" evaluation, I get an accuracy of "
         << currentAccuracy << "%\n\n";

    cout << "Beginning search.\n\n";

    // At each level, try removing one feature at a time
    while (currentSetOfFeatures.size() > 1) {
        int bestIndexToRemove = -1;       // index in currentSetOfFeatures
        double bestAccuracyThisLevel = -1.0;

          // Try removing each feature once
        for (int i = 0; i < (int)currentSetOfFeatures.size(); ++i) {
            vector<int> candidateSet = currentSetOfFeatures;
            candidateSet.erase(candidateSet.begin() + i);
            
            double accuracy = evaluateFeatureSet(candidateSet);
            cout << "\tUsing feature(s) "
                 << featureSetToString(candidateSet)
                 << " accuracy is " << accuracy << "%\n";

            if (accuracy > bestAccuracyThisLevel) {
                bestAccuracyThisLevel = accuracy;
                bestIndexToRemove = i;
            }
        }
        cout << "\n";

        if (bestIndexToRemove == -1) {
            break; 
        }
        // Build the new set after removing the chosen feature
        vector<int> newSet = currentSetOfFeatures;
        newSet.erase(newSet.begin() + bestIndexToRemove);

        cout << "Feature set " << featureSetToString(newSet)
             << " was best, accuracy is " << bestAccuracyThisLevel << "%\n\n";

        // Update current set
        currentSetOfFeatures = newSet;
        currentAccuracy = bestAccuracyThisLevel;

        // Warning if accuracy falls compared to best overall
        if (currentAccuracy < bestOverallAccuracy) {
            cout << "(Warning, Accuracy has decreased!)\n";
        }

        // Track best overall
        if (currentAccuracy > bestOverallAccuracy) {
            bestOverallAccuracy = currentAccuracy;
            bestOverallSet = currentSetOfFeatures;
        }
    }
     cout << "\nFinished search!! The best feature subset is "
         << featureSetToString(bestOverallSet)
         << ", which has an accuracy of " << bestOverallAccuracy << "%\n\n";
}
