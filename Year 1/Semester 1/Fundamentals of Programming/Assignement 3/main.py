import math
import random
import timeit

import texttable

def generate_random_list(l: list, n: int):
    for i in range(n):
        l.append(random.randint(0, 1000))

'''
    JumpSearch - Time Complexity:
        - The complexity of this algorithm is O(sqrt(n))
        - Best case: if it's in the first block of length sqrt(n)
        - Worst case: if it's in the last block of length sqrt(n)
        
    JumpSearch - Space Complexity:
        - JumpSearch requires O(1) additional space, it uses just variables
'''

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

'''
    InsertSort - Time Complexity:
        - T(n) = (n - 1) + (n - 2) + ... + 1 = (n - 1) * n / 2 = (n^2 - n) / 2 => Theta(n^2)
        
        - Best case: if the list is already sorted in the right order
                     then the while loop will never be executed ->  O(n)
                     
        - Worst case: if the list is sorted, but in reverse order
                      then the while loop will execute j iterations each time -> O(n^2)
                      
        - Average case: if the list is randomly ordered -> O(n^2)
            
    InsertSort - Space Complexity:
        - InsertSort requires O(1) additional space, it uses just variables
'''

def insert_sort(l: list, nr_steps: int):
    n = len(l)
    steps = 0
    for i in range(1, n):   # n steps, so O(n)
        ok = False
        value = l[i]
        j = i - 1

        while j >= 0 and value < l[j]:  # in the worst case: 1 it, 2 it, ... , (n - 1) iterations
            ok = True
            l[j + 1] = l[j]
            j -= 1

        l[j + 1] = value

        if ok == True:
            steps += 1

        if steps % nr_steps == 0 and ok == True and nr_steps != -1:
            print_the_list(l, steps)

def sorted_list(l):
    n = len(l)
    for i in range(1, n):
        if l[i - 1] > l[i]:
            return False

    return True

'''
    ShellSort - Time Complexity:
        - Best case: if the list is already sorted in the right order
                     the the most inner while loop will never be executed -> O(n*log(n))
                     
        - Worst case: if all the elements that form the second half of the sorted list
                      are placed on the even positions and in reverse order, and the other
                      half is placed on the odd positions, also in reverse order
                      this happens because these numbers will be compared just when the gap will be 1 -> O(n^2)
        
        - Average case: if the list is randomly ordered -> O(n*log(n))
        
    ShellSort - Space Complexity:
        - ShellSort requires O(1) additional space, it uses just variables
'''

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

                if steps % nr_steps == 0 and steps != 0 and ok == True and nr_steps != -1:
                    print_the_list(l, steps)

                i = i - gap

            j += 1

        gap //= 2

def print_the_list(l, steps):
    print("The list at step", steps, ":", l)

def best_case_insert_sort(l_insert, n):
    for i in range(1, n + 1):
        l_insert.append(i)

def best_case_shell_sort(l_shell, n):
    for i in range(1, n + 1):
        l_shell.append(i)

def worst_case_insert_sort(l_insert, n):
    for i in range(n, 0, -1):
        l_insert.append(i)

def worst_case_shell_sort(l_shell, n):
    i = int(n / 2)
    j = n
    while i >= 1:
        l_shell.append(i)
        l_shell.append(j)
        i -= 1
        j -= 1

def jump_search_sorted_list(l_jump, n):
    for i in range(1, n + 1):
        l_jump.append(i)

l = []
print("Please choose one of the following options")
while True:
    print("1) Generate a list")
    print("2) Search for an item")
    print("3) Sort the list using Insert Sort")
    print("4) Sort the list using Shell Sort")
    print("5) Exit the program")
    print("6) Best case for each algorithm")
    print("7) Average case for each algorithm")
    print("8) Worst case for each algorithm")

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
    elif cmd == "6":
        table = texttable.Texttable()
        table.add_row(['Length', 'Insertion Sort', 'Shell Sort', 'Jump Search'])

        for k in [1000, 2000, 4000, 8000, 16000]:
            l_insert = []
            l_shell = []
            best_case_shell_sort(l_shell, k)
            best_case_insert_sort(l_insert, k)

            start_insert = timeit.default_timer()
            insert_sort(l_insert, -1)
            end_insert = timeit.default_timer()

            start_shell = timeit.default_timer()
            shell_sort(l_shell, -1)
            end_shell = timeit.default_timer()

            l_jump = []   # adjust the list to see a result
            jump_search_sorted_list(l_jump, 10000 * k)
            start_jump = timeit.default_timer()
            y = jump_search(l_jump, int(math.sqrt(10000 * k) - 1))
            end_jump = timeit.default_timer()
            table.add_row([k, end_insert - start_insert, end_shell - start_shell, end_jump - start_jump])

        print(table.draw())

    elif cmd == "7":
        table = texttable.Texttable()
        table.add_row(['Length', 'Insertion Sort', 'Shell Sort', 'Jump Search'])

        for k in [1000, 2000, 4000, 8000, 16000]:
            l_insert = []
            generate_random_list(l_insert, k)
            l_shell = l_insert

            start_insert = timeit.default_timer()
            insert_sort(l_insert, -1)
            end_insert = timeit.default_timer()
    
            start_shell = timeit.default_timer()
            shell_sort(l_shell, -1)
            end_shell = timeit.default_timer()

            l_jump = [] # adjust the list to see a result
            jump_search_sorted_list(l_jump, 10000 * k)
            start_jump = timeit.default_timer()
            y = jump_search(l_jump, 5000 * k)
            end_jump = timeit.default_timer()
            table.add_row([k, end_insert - start_insert, end_shell - start_shell, end_jump - start_jump])

        print(table.draw())
    elif cmd == "8":
        table = texttable.Texttable()
        table.add_row(['Length', 'Insertion Sort', 'Shell Sort', 'Jump Search'])

        for k in [1000, 2000, 4000, 8000, 16000]:
            l_insert = []
            worst_case_insert_sort(l_insert, k)
            l_shell = []
            worst_case_shell_sort(l_shell, k)

            start_insert = timeit.default_timer()
            insert_sort(l_insert, -1)
            end_insert = timeit.default_timer()

            start_shell = timeit.default_timer()
            shell_sort(l_shell, -1)
            end_shell = timeit.default_timer()

            l_jump = []  # adjust the list to see a result
            jump_search_sorted_list(l_jump, 10000 * k)
            start_jump = timeit.default_timer()
            y = jump_search(l_jump, 10000 * k - 1)
            end_jump = timeit.default_timer()
            table.add_row([k, end_insert - start_insert, end_shell - start_shell, end_jump - start_jump])

        print(table.draw())
    else:
        print("Bad command!")