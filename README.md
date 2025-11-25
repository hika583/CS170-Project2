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

### Trace for Forward Selection:
<img width="609" height="525" alt="截屏2025-11-24 下午3 51 24" src="https://github.com/user-attachments/assets/cdc1dd28-4371-4fa5-abfc-eb584da9ab26" />

## Backward Elimination

### Implementation

The  `backwardElimination` algorithm in this project is also implemented as a greedy search procedure, but it works in the opposite direction of Forward Selection. Instead of starting from an empty set, it begins with the full set of features.

It initializes one main list:
1. **currentSetOfFeatures** – initially contains all features from 1 to `totalFeatures`

The function first evaluates this full feature set using the stub evaluation function and prints the baseline accuracy. Then, at each search level, the algorithm considers removing each feature one at a time. For each candidate removal:

* it constructs a temporary set by copying `currentSetOfFeatures` and erasing a single feature
* it evaluates this reduced set using the evaluation function
* it prints the accuracy according to the assignment’s trace format

After evaluating all possible one-feature removals at that level, the algorithm identifies which removal produced the highest accuracy. It then:

* permanently removes that feature from `currentSetOfFeatures`
* continues the search with this smaller feature set

This process repeats, gradually shrinking the feature set as the algorithm removes one feature per level.

Just like in Forward Selection, the algorithm keeps track of the best overall subset and best accuracy seen during the entire search. After each level, if the newly chosen feature set’s accuracy is lower than the global best so far, the function prints the required warning message. When the search finishes (i.e., when only one feature remains in `currentSetOfFeatures`), the algorithm reports the best feature subset and its accuracy observed at any point during the search, which may have any size between 1 and the total number of features.

## Time Complexity (Big-O Analysis)

The Backward Elimination algorithm evaluates:
* d different (d - 1)-feature subsets at the first level
* d - 1 subsets at the next level
* d - 2 at the next, and so on, down to 1

  This gives total of

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

### Trace for Backward Elimination:
<img width="585" height="447" alt="截屏2025-11-24 下午3 51 31" src="https://github.com/user-attachments/assets/90734aa8-4c30-41ef-bd30-0161a1b3d3bc" />
