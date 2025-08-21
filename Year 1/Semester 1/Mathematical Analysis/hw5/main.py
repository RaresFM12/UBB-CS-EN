import matplotlib.pyplot as plt
import numpy as np

# Define the functions and their derivates
def f1(x):
    return x ** 2

def df1(x):
    return 2 * x

def f2(x):
    return x ** 4 - 3 * x ** 2 + 1 # Non-convex function

def df2(x):
    return 4 * x ** 3 - 6 * x

def gradient_descent(f, df, x0, eta, max_iter=10000, max_value = 1e10):
    iter = 0
    x = x0
    xs = [x0] # list to store x values

    while iter < max_iter:
        x_new = x - eta * df(x)
        if abs(f(x_new)) > max_value:
            print("Divergence!")
            break

        x = x_new
        xs.append(x) # store x value
        iter += 1

    return xs, iter

x0 = 1

# Part a
eta = 0.01
xs, num_iter = gradient_descent(f1, df1, x0, eta)
print(f"Part a: For eta={eta}, minimum of f1: {xs[-1]:.6f} (found in {num_iter} iterations")

# Plot f1
x = np.linspace(-1, 1, 400)
y = f1(x)
plt.plot(x, y, label="f1")

# Plot path of gradient descent
plt.plot(xs, [f1(x) for x in xs], 'o-', label="Path of gradient descent")

# Add horizontal line at y = 0
plt.axhline(0, color='r', linestyle='--', label="Minimum of f1")

plt.title("Convergence of gradient descent for small learning rate")
plt.xlabel("x")
plt.ylabel("f1(x)")
plt.legend()
plt.show()

# Part b
etas = [0.01, 0.1, 0.5, 1.0] # different values of eta
for eta in etas:
    xs, num_iter = gradient_descent(f1, df1, x0, eta)
    print(f"Part b: For eta={eta}, the method converged to the minimum of f1: {xs[-1]:.6f} in {num_iter} iterations")
    plt.plot([f1(x) for x in xs], label=f"eta={eta}")

plt.title("Convergence of gradient descent for different learning rates")
plt.xlabel("Iteration")
plt.ylabel("f1(x)")
plt.legend()
plt.show()

# Part c
etas = [1.1, 1.5, 2.0] # different large values of eta
for eta in etas:
    xs, num_iter = gradient_descent(f1, df1, x0, eta)
    if xs[-1] > 1e10:
        print(f"Part c: For eta={eta}, the method diverged")
    else:
        print(f"Part c: For eta={eta}, the method converged to the minimum of f1: {xs[-1]:.6f} in {num_iter} iterations")

    plt.plot([f1(x) for x in xs if f1(x) < 1e10], label=f"eta={eta}")

plt.title("Potential divergence of gradient descent for large learning rates")
plt.xlabel("Iteration")
plt.ylabel("f1(x)")
plt.xlim([0, 100]) # adjust x-axis range
plt.ylim([0, 100]) # adjust y-axis range
plt.legend()
plt.show()

# Part d
eta = 0.01
xs, num_iter = gradient_descent(f2, df2, x0, eta)
print(f"Part d: For eta={eta}, minimum of f2: {xs[-1]:.6f} (found in {num_iter} iterations")

# Plot f2
x = np.linspace(-2, 2, 400)
y = f2(x)
plt.plot(x, y, label="f2")

# Plot path of gradient descent
plt.plot(xs, [f2(x) for x in xs], 'o-', label="Path of gradient descent")

plt.title("Gradient descent can get stuck in a local minimum for non-convex functions")
plt.xlabel("x")
plt.ylabel("f2(x) = x^4 - 3x^2 + 1")
plt.legend()
plt.show()

