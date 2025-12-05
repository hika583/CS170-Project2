#include "dataset.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>

// Read dataset from file: each line "label f1 f2 ... fn"
vector<Instance> loadDataset(const string& filename) {
    vector<Instance> data;
    ifstream in(filename);

    if (!in.is_open()) {
        cerr << "Error: cannot open file " << filename << endl;
        return data;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        vector<string> tokens;
        string tok;

        // split the whole line into tokens first
        while (ss >> tok) {
            tokens.push_back(tok);
        }

        // we need at least 1 label + 1 feature
        if (tokens.size() < 2) continue;

        Instance inst;

        // first token is the label
        inst.label = stoi(tokens[0]);

        // remaining tokens are features
        for (size_t i = 1; i < tokens.size(); ++i) {
            inst.features.push_back(stod(tokens[i]));
        }

        data.push_back(inst);
    }

    return data;
}

// z-score normalize each feature column
void normalizeDataset(vector<Instance>& data) {
    if (data.empty()) return;

    int n = data.size();
    int d = data[0].features.size();

    vector<double> mean(d, 0.0);
    vector<double> stdev(d, 0.0);

    // compute means
    for (auto& inst : data)
        for (int j = 0; j < d; ++j)
            mean[j] += inst.features[j];

    for (int j = 0; j < d; ++j)
        mean[j] /= n;

    // compute stdev
    for (auto& inst : data)
        for (int j = 0; j < d; ++j) {
            double diff = inst.features[j] - mean[j];
            stdev[j] += diff * diff;
        }

    for (int j = 0; j < d; ++j) {
        stdev[j] = sqrt(stdev[j] / n);
        if (stdev[j] == 0) stdev[j] = 1; // avoid division by zero
    }

    // normalize values
    for (auto& inst : data)
        for (int j = 0; j < d; ++j)
            inst.features[j] = (inst.features[j] - mean[j]) / stdev[j];
}