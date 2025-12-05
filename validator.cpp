// validator.cpp
#include "validator.h"
#include <chrono>
#include <iostream>

using namespace std;

double Validator::leaveOneOutValidation(const vector<Instance>& data,
                                        const vector<int>& featureSubset,
                                        bool verbose)
{
    int N = static_cast<int>(data.size());
    if (N == 0) {
        cout << "Validator: dataset is empty.\n";
        return 0.0;
    }

    int correct = 0;

    auto startTime = chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) {
        // Build training set = all instances except i
        vector<Instance> trainSet;
        trainSet.reserve(N - 1);
        for (int j = 0; j < N; ++j) {
            if (j != i) {
                trainSet.push_back(data[j]);
            }
        }

        // Train classifier on trainSet
        NNClassifier nn;
        nn.Train(trainSet);

        // Test on the left-out instance
        const Instance& testInst = data[i];
        int predicted = nn.Test(testInst, featureSubset);
        int actual    = testInst.label;

        if (predicted == actual) {
            correct++;
        }

        if (verbose) {
            cout << "LOOCV step " << (i + 1) << "/" << N
                 << " | predicted=" << predicted
                 << " actual=" << actual
                 << (predicted == actual ? " [correct]" : " [wrong]")
                 << '\n';
        }
    }

    auto endTime = chrono::high_resolution_clock::now();
    double elapsedSeconds =
        chrono::duration<double>(endTime - startTime).count();

    double accuracy = static_cast<double>(correct) / N;

    cout << "\nFeature subset {";
    for (size_t k = 0; k < featureSubset.size(); ++k) {
        cout << featureSubset[k];
        if (k + 1 < featureSubset.size()) cout << ",";
    }
    cout << "} => Correct: " << correct << "/" << N
         << " | Accuracy: " << accuracy
         << " | Time: " << elapsedSeconds << " seconds\n\n";

    return accuracy;
}
