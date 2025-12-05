import pandas as pd
import matplotlib.pyplot as plt

# --------------------------------------------------
# Load the exported CSVs
# --------------------------------------------------
small = pd.read_csv("small_f5_f3.csv")
large = pd.read_csv("large_f27_f1.csv")

# Sanity print (optional)
print("Small head:")
print(small.head())
print("\nLarge head:")
print(large.head())

# --------------------------------------------------
# Create figure with 2 subplots: Small | Large
# --------------------------------------------------
fig, axes = plt.subplots(1, 2, figsize=(10, 4))

# ---------------- Small dataset plot ----------------
ax = axes[0]

# Assuming labels are 1 and 2
class1_small = small[small["label"] == 1]
class2_small = small[small["label"] == 2]

ax.scatter(class1_small["featureA"], class1_small["featureB"],
           marker="o", edgecolors="black", linewidths=0.5, label="Class 1")
ax.scatter(class2_small["featureA"], class2_small["featureB"],
           marker="x", label="Class 2")

ax.set_title("Small Dataset (Features 5 vs 3)")
ax.set_xlabel("Feature 5")
ax.set_ylabel("Feature 3")
ax.legend()

# ---------------- Large dataset plot ----------------
ax = axes[1]

class1_large = large[large["label"] == 1]
class2_large = large[large["label"] == 2]

ax.scatter(class1_large["featureA"], class1_large["featureB"],
           marker="o", edgecolors="black", linewidths=0.5, label="Class 1")
ax.scatter(class2_large["featureA"], class2_large["featureB"],
           marker="x", label="Class 2")

ax.set_title("Large Dataset (Features 27 vs 1)")
ax.set_xlabel("Feature 27")
ax.set_ylabel("Feature 1")
ax.legend()

plt.tight_layout()

# Save to file for report
plt.savefig("small_large_scatter.png", dpi=300)

# Or show interactively
plt.show()
