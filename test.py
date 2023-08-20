
import numpy as np
import json
import matplotlib.pyplot as plt

raw_data='{"x":[-40.074,-15.03,9.94,35.057,60.027,84.997,109.966,134.936,160.128],"y":[6.63,7.771,9.116,10.666,12.437,14.327,16.609,19.096,21.837]}'
parsed_data = json.loads(raw_data)

x_values = np.array(parsed_data['x'])
y_values = np.array(parsed_data['y'])

coefficients = np.polyfit(x_values, y_values, 2)

bard_coefficients = [ 5.94386683e+00,  -2.07571718e-01,   5.65122251e-03,  -4.73878308e-06]

plt.scatter(x_values, y_values, marker='x', linestyle='-', color='b')
#plt.plot(x_values, np.polyval(coefficients, x_values), color='red', label='2nd')
plt.plot(x_values, np.polyval(bard_coefficients, x_values), color='green', label='bard')
plt.xlabel('Temp')
plt.ylabel('R, KOhm')
plt.grid(True)
plt.show()

for i in range(len(coefficients)):
    print(f"{coefficients[i]:.4f}")

val = np.polyval(coefficients, 25)
print(f"For 25C -> {val:.4f}")
