#ifndef NN_CLASSIFIER_H
#define NN_CLASSIFIER_H

#include <vector>
#include "dataset.h"   // Contains the Instance struct
using namespace std;

class NNClassifier {
public:
    // Store the dataset for later use
    void Train(const vector<Instance>& trainingData);

    int Test(const Instance& testInstance,
                const vector<int>& featureSubset) const;

private:
    vector<Instance> trainData;

    // Compute Euclidean distance using only the selected features
    double euclideanDistance(const Instance& a,
                             const Instance& b,
                             const vector<int>& featureSubset) const;
};

#endif
