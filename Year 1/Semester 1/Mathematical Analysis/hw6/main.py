import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return np.sin(x)   # Example function

def f_prime_exact(x):
    return np.cos(x)   # Exact derivative

def forward_difference(f, x, h):
    return (f(x + h) - f(x)) / h

def centered_difference(f, x, h):
    return (f(x + h) - f(x - h)) / (2 * h)

def compute_errors(f, f_prime_exact, x, h_values):
    forward_errors = np.abs(forward_difference(f, x, h_values) - f_prime_exact(x))
    centered_errors = np.abs(centered_difference(f, x, h_values) - f_prime_exact(x))
    return forward_errors, centered_errors

def plot_errors(h_values, forward_errors, centered_errors):
    plt.figure(figsize=(10, 6))
    plt.loglog(h_values, forward_errors, label="Forward Difference Error (O(h))")
    plt.loglog(h_values, centered_errors, label="Centered Difference Error (O(h^2))")
    plt.xlabel("Step size h")
    plt.ylabel("Error")
    plt.title("Error Analysis of Finite Difference Approximations")
    plt.legend()
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.show()

def main():
    x = np.pi / 4
    h_values = np.logspace(-8, -1, 100)
    forward_errors, centered_errors = compute_errors(f, f_prime_exact, x, h_values)
    plot_errors(h_values, forward_errors, centered_errors)

if __name__ == "__main__":
    main()

