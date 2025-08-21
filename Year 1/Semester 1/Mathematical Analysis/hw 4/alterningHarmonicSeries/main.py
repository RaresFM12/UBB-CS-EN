import math
import matplotlib.pyplot as plt
from matplotlib.lines import lineStyles

n_max = 501
sum_values = []
partial_sum = 0

for i in range(1, n_max):
    term = ((-1) ** (i + 1)) * (1 / i)
    partial_sum += term
    sum_values.append(partial_sum)

ln2 = math.log(2)

plt.plot(range(1, n_max), sum_values, label="Partial Sum")
plt.axhline(ln2, color='red', linestyle='--', label="ln(2)")

plt.xlabel("Number of terms")
plt.ylabel("Sum Value")
plt.title("Sum of the Alternating Harmonic Series (up to 500) vs ln(2)")
plt.legend()
plt.grid(True)
plt.show()