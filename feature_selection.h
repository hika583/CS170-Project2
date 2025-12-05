#ifndef FEATURE_SELECTION_H
#define FEATURE_SELECTION_H

#include <vector>
#include <string>
#include "dataset.h"
#include "validator.h"

// Pretty-print feature subsets
std::string featureSetToString(const std::vector<int>& features);

// Forward selection using LOOCV
void forwardSelection(const std::vector<Instance>& data,
                      int totalFeatures,
                      Validator& v);

// Backward elimination using LOOCV
void backwardElimination(const std::vector<Instance>& data,
                         int totalFeatures,
                         Validator& v);

#endif