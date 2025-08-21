# problem 7



def print_the_list(l):
    print(l)

def backtracking_recursive(l, n, k, v):
    if n == 0:                                      # if the list has just 1 element
        print_the_list(l)
        return

    if k == 2 * n:                                  # if we arrived at the last position
        if l[2 * n - 1] != 0:                       # if the element that has the index 2n-1 is different
            print_the_list(l)                       # from 0, then it's OK!

        return

    for i in v:
        if l[k - 1] != i:                           # if the previous element is different from i
            l[k] = i
            backtracking_recursive(l, n, k + 1, v)

v = [-1, 0, 1]
n = int(input("Number n will have the value: "))
l = [-2] * (2 * n + 1)                              # create a list with 2n+1 elements, all of them -2
l[0] = 0
l[2 * n] = 0

backtracking_recursive(l, n, 1, v)