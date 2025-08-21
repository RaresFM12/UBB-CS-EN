import math
import random

def generate_random_list(l: list, n: int):
    for i in range(n):
        l.append(random.randint(0, 1000))

def jump_search(l: list, x: int):
    n = len(l)
    step = math.sqrt(n)

    prev = 0
    while l[int(min(step, n) - 1)] < x:
        prev = step
        step += math.sqrt(n)
        if prev >= n:         # when x is larger than the last element in the list
            return -1

    while l[int(prev)] < x:
        prev += 1

        if prev == min(step, n):     # if the block in which we are searching x has finished or the list has finished
            return -1

    if l[int(prev)] == x:
        return int(prev)

    return -1

def insert_sort(l: list, nr_steps: int):
    n = len(l)
    steps = 0
    for i in range(1, n):
        ok = False
        value = l[i]
        j = i - 1

        while j >= 0 and value < l[j]:
            ok = True
            l[j + 1] = l[j]
            j -= 1

        l[j + 1] = value

        if ok == True:
            steps += 1

        if steps % nr_steps == 0 and ok == True:
            print_the_list(l, steps)

def sorted_list(l):
    n = len(l)
    for i in range(1, n):
        if l[i - 1] > l[i]:
            return False

    return True

def shell_sort(l: list, nr_steps: int):
    n = len(l)
    gap = int(n / 2)
    steps = 0

    while gap > 0:
        j = int(gap)

        while j < n:
            i = int(j - gap)
            ok = False

            while i >= 0:
                if l[int(i + gap)] > l[int(i)]:
                    break
                else:
                    ok = True
                    steps += 1
                    l[int(i + gap)], l[int(i)] = l[int(i)], l[int(i + gap)]

                if steps % nr_steps == 0 and steps != 0 and ok == True:
                    print_the_list(l, steps)

                i = i - gap

            j += 1

        gap //= 2

def print_the_list(l, steps):
    print("The list at step", steps, ":", l)

l = []
print("Please choose one of the following options")
while True:
    print("1) Generate a list")
    print("2) Search for an item")
    print("3) Sort the list using Insert Sort")
    print("4) Sort the list using Shell Sort")
    print("5) Exit the program")

    cmd = input("-> ")

    if cmd == "1":
        l = []
        while True:
            try:
                n = int(input("The length of your list will be: "))
                break
            except ValueError:
                print("The length must be a number!")

        generate_random_list(l, n)
        print(l)
    elif cmd == "2":
        if len(l) == 0:
            print("The list is empty!")
            continue

        if sorted_list(l) == True:
            while True:
                try:
                    x = int(input("The item you are looking for is: "))
                    break
                except ValueError:
                    print("The item must be a number!")

            t = jump_search(l, x)
            if t == -1:
                print("The number", x, "was not found in the list!")
            else:
                print("The number", x, "was found in the list and his index is", t)
        else:
            print("The list has to be sorted!!!")
    elif cmd == "3":
        while True:
            try:
                steps = int(input("The number of steps will be: "))
                break
            except ValueError:
                print("The number of steps must be a number!")

        insert_sort(l, steps)
        print("The sorted list:", l)
    elif cmd == "4":
        while True:
            try:
                steps = int(input("The number of steps will be: "))
                break
            except ValueError:
                print("The number of steps must be a number!")

        shell_sort(l, steps)
        print("The sorted list:", l)
    elif cmd == "5":
        break
    else:
        print("Bad command!")