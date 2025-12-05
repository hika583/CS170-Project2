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


## Nearest Neighbor Classifier

The NN classifier in this project follows the standard 1-Nearest Neighbor approach. The Train function simply stores the training instances, since 1-NN is a lazy-learning method and does not build a model. The Test function classifies a new instance by computing the Euclidean distance between the test instance and every stored training instance, using only the selected feature subset. The classifier then returns the label of the closest instance.
Before classification, the dataset is standardized using z-score normalization, ensuring that all features contribute equally to the distance calculation. This prevents large-valued features from dominating the similarity measure.


## Dataset Normalization

As required in the project description, **all datasets are normalized before running LOOCV**.  
Each feature column is independently rescaled to the range **[0, 1]**, ensuring:

- features are comparable in scale  
- no single feature dominates the Euclidean distance  
- distance-based classification behaves consistently  

The small and large datasets are normalized **independently**.


## Leave-One-Out Cross Validation (LOOCV)

The validator evaluates the 1-NN classifier using **Leave-One-Out Cross Validation**.  
For a dataset of size **N**:

1. Select instance *i* as the **test instance**.  
2. Use the remaining **N − 1** instances as the **training set**.  
3. Classify the test instance using 1-NN.  
4. Count whether the prediction was correct.  
5. Repeat for **all N instances**.

The accuracy is computed as:

\[
\text{Accuracy} = \frac{\text{Number of Correct Predictions}}{N}
\]

A high-resolution timer records the **total runtime** for the entire LOOCV evaluation.  

For the **small dataset (100 instances)**, verbose mode is enabled, printing each step's predicted and actual labels, producing a detailed trace.


## Feature Subset Evaluation (Part II Results)

The validator was applied to the feature subsets specified in the project handout:

- **Small dataset** → subset **{3, 5, 7}**  
- **Large dataset** → subset **{1, 15, 27}**

The results obtained match the expected accuracies from the project document:

- Small dataset accuracy ≈ **0.89**  
- Large dataset accuracy ≈ **0.95**

These results confirm that:

- dataset normalization  
- the NN classifier  
- and the LOOCV validator  

were all implemented correctly.

## Part II – Sample Program Output (CLI)

Welcome to Hikaru Shimada and Tristan Zhao's Feature Selection & NN Project.
Please enter total number of features for feature selection (Part I / III): 3

Type the number of the option you want to run:
1) Forward Selection (Part I)
2) Backward Elimination (Part I)
3) Part II: Run NN + Validator on sample datasets
Choice: 3

### **Small Dataset (Verbose LOOCV Trace)**

<details>
<summary>Click to expand full LOOCV trace (100 steps)</summary>

==============================
 Part II: Small Dataset Test
==============================
Loaded 100 instances from small-test-dataset.txt
Normalizing small dataset...
Normalization done.
Running LOOCV with feature subset {3,5,7}...

LOOCV step 1/100 | predicted=2 actual=2 [correct]
LOOCV step 2/100 | predicted=2 actual=2 [correct]
LOOCV step 3/100 | predicted=2 actual=2 [correct]
LOOCV step 4/100 | predicted=1 actual=2 [wrong]
LOOCV step 5/100 | predicted=2 actual=2 [correct]
...
LOOCV step 98/100 | predicted=2 actual=1 [wrong]
LOOCV step 99/100 | predicted=2 actual=2 [correct]
LOOCV step 100/100 | predicted=2 actual=2 [correct]

Feature subset {3,5,7} => Correct: 89/100 | Accuracy: 0.89
Time: 0.00166979 seconds

Final accuracy on small-test-dataset.txt with features {3,5,7}: 0.89

</details>

---

### **Large Dataset (Summary Only)**

==============================
 Part II: Large Dataset Test
==============================
Loaded 1000 instances from large-test-dataset.txt
Normalizing large dataset...
Normalization done.
Running LOOCV with feature subset {1,15,27}...

Feature subset {1,15,27} => Correct: 950/1000 | Accuracy: 0.95
Time: 0.102173 seconds

Final accuracy on large-test-dataset.txt with features {1,15,27}: 0.95

Part II experiments finished.