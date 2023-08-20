import matplotlib.pyplot as plt
import numpy as np
from numpy.polynomial.polynomial import Polynomial

# Load data from the file, temp, C to V
data = []
data.append((0, 0))
with open('temp-measurement.txt', 'r') as file:
    for line_num, line in enumerate(file):
        if line_num == 0:
            continue  # Skip the first line
        x, y = line.strip().split('	')
        data.append((float(x), float(y)))

x_values = np.array([point[1] for point in data])
y_values = np.array([point[0] for point in data])

# Perform quadratic regression
coefficients = np.polyfit(x_values, y_values, 1)
# curve = coefficients[0] * x_values**3 + \
#     coefficients[1] * x_values**2 + \
#     coefficients[2] * x_values + coefficients[3]

curve = np.polyval(coefficients, x_values)
print("coefficients", coefficients)

plt.scatter(x_values, y_values, marker='x', color='blue', label='Data')
plt.plot(x_values, curve, color='red', label='*Curve')
plt.ylabel('Temp, C')
plt.xlabel('Voltage, V')
plt.legend()
plt.grid(True)

# Save the figure to an image file
plt.savefig('temp-measurement.png')

plt.show()



