// main.cpp
#include <iostream>
#include <vector>
#include <algorithm>

#include "feature_selection.h"
#include "dataset.h"
#include "nn_classifier.h"
#include "validator.h"

using namespace std;

// Helper to run the Part II experiments and print trace
void runPartIIExperiments() {
    Validator v;

    // ---------- SMALL DATASET ----------
    cout << "==============================\n";
    cout << " Part II: Small Dataset Test\n";
    cout << "==============================\n";

    vector<Instance> smallData = loadDataset("small-test-dataset.txt");
    cout << "Loaded " << smallData.size()
         << " instances from small-test-dataset.txt\n";

    if (smallData.empty()) {
        cout << "Error: small-test-dataset.txt is empty or could not be loaded.\n";
    } else {
        cout << "Normalizing small dataset...\n";
        normalizeDataset(smallData);
        cout << "Normalization done.\n";

        // Feature subset {3,5,7} as specified in the assignment
        vector<int> smallSubset = {3, 5, 7};
        cout << "Running LOOCV with feature subset {3,5,7}...\n\n";

        // verbose = true to show step-by-step trace for the small dataset
        double smallAcc = v.leaveOneOutValidation(smallData, smallSubset, true);

        cout << "Final accuracy on small-test-dataset.txt "
             << "with features {3,5,7}: " << smallAcc << "\n\n";
    }

    // ---------- LARGE DATASET ----------
    cout << "==============================\n";
    cout << " Part II: Large Dataset Test\n";
    cout << "==============================\n";

    vector<Instance> largeData = loadDataset("large-test-dataset.txt");
    cout << "Loaded " << largeData.size()
         << " instances from large-test-dataset.txt\n";

    if (largeData.empty()) {
        cout << "Error: large-test-dataset.txt is empty or could not be loaded.\n";
    } else {
        cout << "Normalizing large dataset...\n";
        normalizeDataset(largeData);
        cout << "Normalization done.\n";

        // Feature subset {1,15,27} as specified in the assignment
        vector<int> largeSubset = {1, 15, 27};
        cout << "Running LOOCV with feature subset {1,15,27}...\n\n";

        // verbose = false (1000 lines of trace would be huge)
        double largeAcc = v.leaveOneOutValidation(largeData, largeSubset, false);

        cout << "Final accuracy on large-test-dataset.txt "
             << "with features {1,15,27}: " << largeAcc << "\n\n";
    }

    cout << "Part II experiments finished.\n\n";
}

int main() {
    cout << "Welcome to Hikaru Shimada and Tristan Zhao's Feature Selection & NN Project.\n\n";

    cout << "Please enter total number of features for feature selection (Part I / III): ";
    int totalFeatures;
    cin >> totalFeatures;

    cout << "\nType the number of the option you want to run:\n";
    cout << "1) Forward Selection (Part I)\n";
    cout << "2) Backward Elimination (Part I)\n";
    cout << "3) Part II: Run NN + Validator on sample datasets\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;
    cout << "\n";

    if (choice == 1) {
        forwardSelection(totalFeatures);
    } else if (choice == 2) {
        backwardElimination(totalFeatures);
    } else if (choice == 3) {
        runPartIIExperiments();
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
