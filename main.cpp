// main.cpp
#include <iostream>
#include "feature_selection.h"

using namespace std;

int main() {
    cout << "Welcome to Hikaru Shimada and Tristan Zhao's Feature Selection Algorithm.\n";
    cout << "Please enter total number of features: ";

    int totalFeatures;
    cin >> totalFeatures;

    cout << "Type the number of the algorithm you want to run.\n";
    cout << "1) Forward Selection\n";
    cout << "2) Backward Elimination\n";
    cout << "3) (Optional) Special Algorithm (not implemented yet).\n";

    int choice;
    cin >> choice;

    if (choice == 1) {
        forwardSelection(totalFeatures);
    } else if (choice == 2) {
        backwardElimination(totalFeatures);
    } else {
        cout << "Special algorithm not implemented yet.\n";
    }

    return 0;
}
