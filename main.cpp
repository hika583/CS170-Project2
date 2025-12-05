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

// Helper to load a dataset by choice and run Forward/Backward selection (Part III)
void runPartIIISelection(bool useForward) {
    cout << "Select dataset for feature selection:\n";
    cout << " 1) small-test-dataset.txt\n";
    cout << " 2) large-test-dataset.txt\n";
    cout << " 3) titanic-dataset.txt\n";   // <-- adjust name if needed
    cout << "Choice: ";

    int dchoice;
    cin >> dchoice;

    string filename;
    if (dchoice == 1) {
        filename = "small-test-dataset.txt";
    } else if (dchoice == 2) {
        filename = "large-test-dataset.txt";
    } else if (dchoice == 3) {
        filename = "titanic-dataset.txt";  // change if your file has a different name
    } else {
        cout << "Invalid dataset choice.\n";
        return;
    }

    vector<Instance> data = loadDataset(filename);
    cout << "Loaded " << data.size() << " instances from " << filename << "\n";

    if (data.empty()) {
        cout << "Error: dataset is empty or could not be loaded.\n";
        return;
    }

    cout << "Do you want to normalize the dataset? (y/n): ";
    char yn;
    cin >> yn;

    if (yn == 'y' || yn == 'Y') {
        cout << "Normalizing dataset...\n";
        normalizeDataset(data);
        cout << "Normalization done.\n\n";
    } else {
        cout << "Skipping normalization.\n\n";
    }

    int totalFeatures = static_cast<int>(data[0].features.size());
    cout << "Dataset has " << totalFeatures << " features.\n\n";

    // Create Validator for LOOCV
    Validator v;

    // Optional: default rate with no features
    vector<int> emptySet;
    double defaultAcc = v.leaveOneOutValidation(data, emptySet, false);
    cout << "Running nearest neighbor with no features (default rate), "
            "using \"leaving-one-out\" evaluation, I get an accuracy of "
         << defaultAcc << "%\n\n";

    if (useForward) {
        cout << "Running Forward Selection (LOOCV-based evaluation)...\n\n";
        forwardSelection(data, totalFeatures, v);
    } else {
        cout << "Running Backward Elimination (LOOCV-based evaluation)...\n\n";
        backwardElimination(data, totalFeatures, v);
    }
}


int main() {
    cout << "Welcome to Hikaru Shimada and Tristan Zhao's Feature Selection & NN Project.\n\n";

    cout << "Type the number of the option you want to run:\n";
    cout << "1) Forward Selection with LOOCV (Part III)\n";
    cout << "2) Backward Elimination with LOOCV (Part III)\n";
    cout << "3) Part II: Run NN + Validator on sample datasets\n";
    cout << "Choice: ";

    int choice;
    cin >> choice;
    cout << "\n";

    if (choice == 1) {
        runPartIIISelection(true);
    } else if (choice == 2) {
        runPartIIISelection(false);
    } else if (choice == 3) {
        runPartIIExperiments();
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}
