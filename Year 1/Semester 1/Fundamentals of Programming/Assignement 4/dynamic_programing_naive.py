# problem 7

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

"""
    Time complexity: O(2^n) -> we have only 2 posibilities
    Space Complexity: O(n) -> recursion stack space
    
    k - actual position
    l - list
    n - len(l)
    sum - it's the sum
    f - the list which stores the indexes of the values that are in one of the partial sums
    found - the list which uses the first element as an indicator to tell us we have already 1 possibility
"""

def determine_subset(k, l, n, sum, f, found):
    if sum == 0:
        if found[0] == False:
            print_the_subset(l, f, n)

        found[0] = True
        return True

    if k >= n:
        return False

    if l[k] > sum:
        return determine_subset(k + 1, l, n, sum, f, found)

    f.append(k)
    x = determine_subset(k + 1, l, n, sum - l[k], f, found)
    f.pop()

    y = determine_subset(k + 1, l, n, sum, f, found)

    return x or y


n = input("Your set will be: ").split()
l = []
s = 0

for i in n:
    l.append(int(i))
    s += int(i)

n = len(l)
f = []

if s % 2 == 1:
    print("The list cannot be partitioned into 2 subsets!!!")
else:
    found = [False]
    if determine_subset(0, l, n, s // 2, f, found) == True:
        print("The list can be partitioned into 2 subsets!!!")
    else:
        print("The list cannot be partitioned into 2 subsets!!!")




