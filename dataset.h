#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
using namespace std;

// One row in the dataset: a label and its feature vector
struct Instance {
    int label;                // class label: 1 or 2
    vector<double> features;  // feature values (normalized later)
};

// Load all instances from a text file
vector<Instance> loadDataset(const string& filename);

// Normalize each feature column (z-score: (x - mean) / stddev)
void normalizeDataset(vector<Instance>& data);

#endif
