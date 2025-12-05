#include "nn_classifier.h"
#include <cmath>
#include <limits>


void NNClassifier::Train(const vector<Instance>& data) {
    trainData = data;
}

double NNClassifier::euclideanDistance(
    const Instance& a,
    const Instance& b,
    const vector<int>& subset) const {
        
    double sum = 0.0;

    for (int f : subset) {
        int idx = f - 1;                // convert from 1-based to 0-based index
        double diff = a.features[idx] - b.features[idx];
        sum += diff * diff;
    }

    return sqrt(sum);
}

int NNClassifier::Test(
    const Instance& testInstance,
    const vector<int>& subset
) const {
    double bestDist = numeric_limits<double>::infinity();
    int bestLabel = -1;

    // Compare the test instance with each training instance
    for (const auto& trainInst : trainData) {
        double dist = euclideanDistance(testInstance, trainInst, subset);

        if (dist < bestDist) {
            bestDist = dist;
            bestLabel = trainInst.label;
        }
    }

    return bestLabel;     // return label of nearest neighbor
}
