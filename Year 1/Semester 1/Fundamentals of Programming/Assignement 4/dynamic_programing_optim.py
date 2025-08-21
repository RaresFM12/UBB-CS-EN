# problem 7

def find_numbers(mat, l, f, i, j):
    if i == 0 or j == 0:
        return

    while mat[i][j - 1] == True:
        j -= 1

    f.append(j - 1)
    find_numbers(mat, l, f, i - l[j - 1], j - 1)

def print_the_subset(l, f, n):
    t1 = []
    t2 = []
    for i in f:
        t1.append(l[i])

    print(t1, end=" ")
    print("and", end=" ")

    for i in range(0, n):
        ok = False
        for j in f:
            if i == j:
                ok = True

        if ok == False:
            t2.append(l[i])

    print(t2)

def print_the_matrix(mat, sum, n):
    for i in range(1, s // 2 + 1):
        for j in range(1, n + 1):
            if mat[i][j] == True:
                print("1 ", end="")
            else:
                print("0 ", end="")

        print("\n", end="")


"""
    Time Complexity: O(sum * n)
    Space Complexity: O(sum * n)
"""

def generate_subset(l, n, sum):
    mat = [[True for i in range(n + 1)] for j in range (s // 2 + 1)]

    for i in range(0, n + 1):
        mat[0][i] = True

    for i in range(1, sum // 2 + 1):
        mat[i][0] = False

    for i in range(1, sum // 2 + 1):
        for j in range(1, n + 1):
            mat[i][j] = mat[i][j - 1]

            if i >= l[j - 1]:
                mat[i][j] = (mat[i][j] or
                              mat[i - l[j - 1]][j - 1])

    if mat[sum // 2][n] == True:
        f = []
        find_numbers(mat, l, f, sum // 2, n)
        print_the_subset(l, f, n)
        print_the_matrix(mat, sum, n)

    return mat[sum // 2][n]

n = input("Your set will be: ").split()
l = []
s = 0

for i in n:
    l.append(int(i))
    s += int(i)

n = len(l)
if s % 2 != 0:
    print("The list cannot be partitioned into 2 subsets!!!")
else:
    if generate_subset(l, n, s) == True:
        print("The list can be partitioned into 2 subsets!!!")
    else:
        print("The list cannot be partitioned into 2 subsets!!!")






