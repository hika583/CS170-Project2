# CS170 Project 2 – Feature Selection

## Main Function

The `main` function serves as the user interface for the program. It first prints a welcome message that includes my name and then prompts the user to enter the total number of features in the dataset. After that, it displays a simple menu allowing the user to choose between **Forward Selection** and **Backward Elimination** (with an option placeholder for a future “special” algorithm).

Based on the user’s choice, `main` calls either the `forwardSelection` or `backwardElimination` function with the given number of features. The function itself does not perform any evaluation or implement search logic; instead, it is responsible only for:

* gathering input
* displaying the menu
* delegating to the appropriate search algorithm

The selected algorithm then prints the detailed trace required by the assignment.

---

## Forward Selection

### Implementation

The `forwardSelection` algorithm in this project is implemented as a greedy search procedure that incrementally builds a subset of features. The function begins by printing the "no features" baseline accuracy using the stub evaluation function.

It then initializes two lists:

1. **currentSetOfFeatures** – starts empty and holds features that have been selected so far
2. **remainingFeatures** – initially contains all features from `1` to `totalFeatures`

At each search level, the algorithm iterates **only over the remaining features**. For each candidate feature:

* it constructs a temporary set by copying the current set and appending the candidate
* it evaluates this temporary set using the evaluation function
* it prints the accuracy according to the assignment’s trace format

The algorithm tracks which candidate feature yields the highest accuracy at that level. After evaluating all candidates:

* the best feature is permanently added to `currentSetOfFeatures`
* that feature is removed from `remainingFeatures`

This design eliminates redundant checks, removes the need for repeated membership lookups, and causes the inner loop to shrink at each level.

The algorithm also keeps track of the **best overall subset** and **best accuracy** seen during the entire search. If a newly selected feature set yields lower accuracy than the global best, the function prints the required warning. When the search finishes, it reports the best subset and its accuracy.

---

## Time Complexity (Big-O Analysis)

The Forward Selection algorithm evaluates:

```
d + (d - 1) + (d - 2) + ... + 1
```

This is the triangular number:

```
(d * (d + 1)) / 2
```

Therefore, the time complexity of Forward Selection is:

### **O(d²)**

where **d** is the total number of features.