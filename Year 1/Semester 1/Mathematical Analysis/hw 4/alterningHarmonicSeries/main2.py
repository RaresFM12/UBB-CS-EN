import math
import matplotlib.pyplot as plt

n_max = 500
sum_values = []
partial_sum = 0

n = 1
while n <= n_max:
    for i in range(10):
        term = 1 / n
        partial_sum += term
        n += 1
        sum_values.append(partial_sum)

    for i in range(10):
        term = -1 / n
        partial_sum += term
        n += 1
        sum_values.append(partial_sum)

ln2 = math.log(2)

plt.plot(range(1, n_max + 1), sum_values, label="Partial Sum")
plt.axhline(ln2, color='red', linestyle='--', label="ln(2)")

plt.xlabel("Number of terms")
plt.ylabel("Sum Value")
plt.title("Sum of the Alternating Harmonic Series (up to 500) vs ln(2) adding 10 positive terms and then 10 negative terms and so on...")
plt.legend()
plt.grid(True)
plt.show()