// // main.cpp
// #include <iostream>
// #include "feature_selection.h"

// using namespace std;

// int main() {
//     cout << "Welcome to Hikaru Shimada and Tristan Zhao's Feature Selection Algorithm.\n";
//     cout << "Please enter total number of features: ";

//     int totalFeatures;
//     cin >> totalFeatures;

//     cout << "Type the number of the algorithm you want to run.\n";
//     cout << "1) Forward Selection\n";
//     cout << "2) Backward Elimination\n";
//     cout << "3) (Optional) Special Algorithm (not implemented yet).\n";

//     int choice;
//     cin >> choice;

//     if (choice == 1) {
//         forwardSelection(totalFeatures);
//     } else if (choice == 2) {
//         backwardElimination(totalFeatures);
//     } else {
//         cout << "Special algorithm not implemented yet.\n";
//     }

//     return 0;
// }


//Testing purpose(delete later)
#include <iostream>
#include <fstream> 
#include <sstream> 
#include <string> 
#include <vector>

#include "dataset.h"
#include "nn_classifier.h"
using namespace std;

int main() {
    // 1) Load small dataset
    vector<Instance> data = loadDataset("large-test-dataset.txt");
    cout << "Loaded " << data.size() << " instances from small-test-dataset.txt\n";

    if (data.empty()) {
        cout << "No data loaded.\n";
        return 0;
    }

    int d = data[0].features.size();
    cout << "Each instance has " << d << " features.\n";

    // 2) Normalize
    normalizeDataset(data);
    cout << "Normalization done.\n";

    // Show first instance for sanity check
    cout << "First instance label: " << data[0].label << "\n";
    cout << "First instance first 3 features (normalized): ";
    for (int j = 0; j < min(d, 3); ++j) {
        cout << data[0].features[j] << " ";
    }
    cout << "\n";

    // 3) Test NNClassifier on ONE instance using the rest as training
    int testIndex = 0;
    vector<Instance> trainSet;
    for (int i = 0; i < (int)data.size(); ++i) {
        if (i == testIndex) continue;
        trainSet.push_back(data[i]);
    }

    // Use features {3, 5, 7} as in the assignment
    vector<int> subset = {3, 5, 7};

    NNClassifier nn;
    nn.Train(trainSet);

    int predicted = nn.Test(data[testIndex], subset);
    int actual    = data[testIndex].label;

    cout << "For instance " << testIndex << ", predicted = "
         << predicted << ", actual = " << actual << "\n";

    return 0;
}
