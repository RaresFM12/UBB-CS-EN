# Solve the problem from the third set here

from math import sqrt

def prime(x) -> bool:
    if x < 2:
        return False

    if x == 2:
        return True

    if x % 2 == 0:
        return False

    for d in range(3, int(sqrt(x)) + 1, 2):
        if x % d == 0:
            return False

    return True

def nr_elements_comp_number(x) -> int:    # this function finds the number of prime divisors of a number
    if prime(x) == True:
        return 1

    if x == 1:
        return 1

    nr_elem = 0
    d = 2

    while x != 1:
        find_prime_div = 0
        while x % d == 0:
            find_prime_div = 1
            x /= d

        if find_prime_div == 1:
            nr_elem += d

        d += 1

    return nr_elem

def the_nth_element(x, nr) -> int:   #   this function finds the n-th element of the sequence
    if prime(x) == True:
        return x


    if x == 1:
        return x

    nr_elem = 0
    d = 2

    while x != 1:
        find_prime_div = 0
        while x % d == 0:
            find_prime_div = 1
            x /= d

        if find_prime_div == 1:
            nr_elem += d

        if nr_elem >= nr:
            return d

        d += 1

    return 0

n = int(input("We have to find the element number: "))
x = 1
cnt = 0
z = 0

while cnt < n:
    nr_elem = nr_elements_comp_number(x)
    if cnt + nr_elem >= n:                # if the number of prime divisors of x + the number of elements
        z = the_nth_element(x, n - cnt)   # which are already in the sequence is greater than n, then we can find the n-th element
        break

    cnt += nr_elem
    x += 1

print("The n-th element is:", z)

