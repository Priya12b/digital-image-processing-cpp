import numpy as np
import matplotlib.pyplot as plt

# Load the data
original = np.loadtxt(
    "../images/outputs/equalization_original.txt"
)

equalized = np.loadtxt(
    "../images/outputs/equalization_equalized.txt"
)

x1 = original[:, 0]
y1 = original[:, 1]

x2 = equalized[:, 0]
y2 = equalized[:, 1]

# Plot 1: Before Equalization
plt.figure()
plt.bar(
    x1,
    y1,
    width=1
)
plt.xlabel("Intensity")
plt.ylabel("Number of Pixels")
plt.title(
    "Histogram Before Equalization"
)
plt.xlim(0, 255)
plt.savefig(
    "../images/outputs/equalization_before.png"
)
plt.close()  # CHANGED: Replaced plt.show() with plt.close()

# Plot 2: After Equalization
plt.figure()
plt.bar(
    x2,
    y2,
    width=1
)
plt.xlabel("Intensity")
plt.ylabel("Number of Pixels")
plt.title(
    "Histogram After Equalization"
)
plt.xlim(0, 255)
plt.savefig(
    "../images/outputs/equalization_after.png"
)
plt.close()  # CHANGED: Replaced plt.show() with plt.close()
