// validator.h
#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include "dataset.h"       // for Instance, loadDataset, normalizeDataset
#include "nn_classifier.h"

class Validator {
public:
    // Run Leave-One-Out Cross Validation using a given feature subset.
    // Returns accuracy in [0,1].
    // If verbose == true, prints a line for each LOOCV step.
    double leaveOneOutValidation(const std::vector<Instance>& data,
                                 const std::vector<int>& featureSubset,
                                 bool verbose = false);
};

#endif // VALIDATOR_H
