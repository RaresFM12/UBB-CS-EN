# problem 7

def print_the_list(l):
    print(l)



def backtracking_iterative(l, n):
    if n == 0:                                      # if the list has just 1 element
        print_the_list(l)
        return

    i = 1

    while i > 0:
        found = False

        while found == False and l[i] <= 0:         # until we find a value that is appropriate
            l[i] += 1

            if i < 2 * n and l[i] != l[i - 1]:      # if it's not the last position and if the value is different from the previous one
                found = True

        if found == False:                          # if we didn't find a value, then we go back
            i -= 1                                  # to the previous position
        elif i < 2 * n - 1:
            i += 1                                  # if we found a value and position is smaller than the second to last position
            l[i] = -2
        elif l[2 * n - 1] != 0 and i == 2 * n - 1:  # if we reached the second to last position and the value is different from 0
            print_the_list(l)


n = int(input("Number n will have the value: "))
l = [-2] * (2 * n + 1)                              # create a list with 2n+1 elements, all of them -2
l[0] = 0
l[2 * n] = 0

backtracking_iterative(l, n)










