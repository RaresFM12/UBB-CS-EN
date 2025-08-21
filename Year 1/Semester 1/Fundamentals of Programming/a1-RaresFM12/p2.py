# Solve the problem from the second set here

def the_smallest_fib_nr(n) -> int:
    x = 1
    y = 1
    z = -1

    if n == 0:
        return 1

    while z <= n:
        z = x + y
        x = y
        y = z

    return z

n = int(input("Our initial number is: "))
m = the_smallest_fib_nr(n)
print("The smallest Fibonacci number larger than", n, "is:", m)
