# Peyton Somerville
# BioInfo HW3
# 2/22/21

import numpy as np
import matplotlib.pyplot as plt

x = np.array([[67, 11.5, 0, 6, 1.8, 1.6, 113, 0.74],            # A
              [148, 14.28, 52, 10.76, -4.5, -12.3, 241, 0.64],  # R
              [96, 12.28, 3.38, 5.41, -3.5, -4.8, 158, 0.63],   # N
              [91, 11.68, 49.7, 2.77, -3.5, -9.2, 151, 0.62],   # D
              [86, 13.46, 1.48, 5.05, 2.5, 2, 140, 0.91],       # C
              [114, 14.45, 3.53, 5.65, -3.5, -4.1, 189, 0.62],  # Q
              [109, 13.57, 49.9, 3.22, -3.5, -8.2, 183, 0.62],  # E
              [48, 3.4, 0, 5.97, -0.4, 1, 85, 0.72],            # G
              [118, 13.69, 51.6, 7.59, -3.2, -3, 194, 0.78],    # H
              [124, 21.4, 0.13, 6.02, 4.5, 3.1, 182, 0.88],     # I
              [124, 21.4, 0.13, 5.98, 3.8, 2.8, 180, 0.85],     # L
              [135, 15.71, 49.5, 9.74, -3.9, -8.8, 211, 0.52],  # K
              [124, 16.25, 1.43, 5.74, 1.9, 3.4, 204, 0.85],    # M
              [135, 19.8, 0.35, 5.48, 2.8, 3.7, 218, 0.88],     # F
              [90, 17.43, 1.58, 6.3, -1.6, -0.2, 143, 0.64],    # P
              [73, 9.47, 1.67, 5.68, -0.8, 0.6, 122, 0.66],     # S
              [93, 15.77, 1.66, 5.66, -0.7, 1.2, 146, 0.7],     # T
              [163, 21.67, 2.1, 5.89, -0.9, 1.9, 259, 0.85],    # W
              [141, 18.03, 1.61, 5.66, -1.3, -0.7, 229, 0.76],  # Y
              [105, 21.57, 0.13, 5.96, 4.2, 2.6, 160, 0.86]])   # V

np.set_printoptions(precision=3, linewidth=100, suppress=True)

print("Original matrix:")
print(x)

z = np.copy(x)
for i in range(8):
    z[:, i] = (x[:, i] - x[:, i].mean())/x[:, i].std()
print("\nNormalized matrix:")
print(z)

c = np.corrcoef(z, rowvar=False)
print("\nCovariance matrix:")
print(c)

e = np.linalg.eigvals(c)
print("\nEigenvalues:")
print(e)

x = list(z[:, 6])
y = list(z[:, 5])
plt.scatter(x, y)
plt.xlabel('First component')
plt.ylabel('Second component')

aa = ['A', 'R', 'N', 'D', 'C', 'Q', 'E', 'G', 'H', 'I', 'L', 'K', 'M', 'F', 'P', 'S', 'T', 'W', 'Y', 'V']
for i in range(20):
    plt.annotate(aa[i], (x[i], y[i]))

plt.show()
