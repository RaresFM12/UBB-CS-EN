# Non UI
import math


def initial_cases(l: list):
    l.append(create_complex_nr("5+6i"))
    l.append(create_complex_nr("4"))
    l.append(create_complex_nr("8i"))
    l.append(create_complex_nr("-9-7i"))
    l.append(create_complex_nr("-i"))
    l.append(create_complex_nr("-10i"))
    l.append(create_complex_nr("-9-7i"))
    l.append(create_complex_nr("-10i"))
    l.append(create_complex_nr("12-3i"))
    l.append(create_complex_nr("19+13i"))
    l.append(create_complex_nr("-6-9i"))
    l.append(create_complex_nr("i"))
    l.append(create_complex_nr("-5"))
    l.append(create_complex_nr("5+i"))
    l.append(create_complex_nr("5-i"))
    l.append(create_complex_nr("-5"))
    l.append(create_complex_nr("5+i"))

def longest_subarray(l: list, arr: list):
    """
    This function finds the length and the elements of the longest subarray of numbers that contains
    at most 3 distinct values
    :param l: the list with complex numbers given by the user
    :param arr: one of the longest subarrays that was found
    :return: the length of the longest subarray that contains at most 3 distinct values
    """
    length = 0
    i_start = -1
    ok = False
    f = [[0, 0], [0, 0], [0, 0]]

    for i in range(len(l)):
        ok = False
        f[0] = l[i].copy()

        for j in range(i + 1, len(l)):
            if get_real(f[0]) != get_real(l[j]) or get_imaginary(f[0]) != get_imaginary(l[j]):
                f[1] = l[j].copy()

                for k in range(j + 1, len(l)):
                    if (l[k] == f[2] and ok == True) or (l[k] == f[1] or l[k] == f[0]):
                        if length < k - i + 1:
                            length = k - i + 1
                            i_start = i
                    elif l[k] != f[0] and l[k] != f[1] and ok == False:
                        f[2] = l[k].copy()
                        ok = True
                        if length < k - i + 1:
                            length = k - i + 1
                            i_start = i
                    elif l[k] != f[0] and l[k] != f[1] and ok == True:
                        if length < k - 1 - i + 1:
                            length = k - 1 - i + 1
                            i_start = i

                        ok = False
                        break

                break
            elif length < j - i + 1:
                length = j - i + 1
                i_start = i

    for i in range(i_start, i_start + length):
        arr.append(l[i])

    return length


def number_modulus(n):
    """
    This function finds the modulus of a complex number
    :param n: the complex number whose modulus we want to find
    :return: modulus of the number(double)
    """
    return math.sqrt(get_real(n) * get_real(n) + get_imaginary(n) * get_imaginary(n))

def longest_increasing_subseq(m: list, s: list, seq: list):
    """
    This function finds the length and elements of the longest increasing subsequence,
    when considering each number's modulus
    :param m: modulus values list
    :param s: the list used for dynamic programming
    :param seq: the list which saves the indexes of the elements from the subsequence
    :return: the length of the longest increasing subsequence
    """
    aux = []
    for i in m:
        aux.append(-1)
        s.append(1)

    for i in range(1, len(m)):
        for j in range(0, i):
            if m[i] > m[j] and s[i] < s[j] + 1:
                s[i] = s[j] + 1
                aux[i] = j

    len_seq = 0
    ind = 0
    for i in range(len(s)):
        if s[i] > len_seq:
            len_seq = s[i]
            ind = i

    seq.append(ind)
    ind = aux[ind]

    while ind != -1:
        seq.append(ind)
        ind = aux[ind]

    return len_seq
""""
# Dictionary
def create_complex_nr(s: str):
    i = 0
    n = ""
    real = 0
    im = 0
    neg = False

    if s == "i":
        complex_nr = {
            "real": 0,
            "imaginary": 0
        }

        set_real(complex_nr, 0)
        set_imaginary(complex_nr, 1)

        return complex_nr

    if s == "-i":
        complex_nr = {
            "real": 0,
            "imaginary": 0
        }

        set_real(complex_nr, 0)
        set_imaginary(complex_nr, -1)

        return complex_nr

    if s[0] == '-':
        neg = True
        i += 1

    while i < len(s) and (s[i] >= '0' and s[i] <= '9'):
        n += s[i]
        i += 1

    if i == len(s):
        real = int(n)
        im = 0

        if neg == True:
            real *= -1

        complex_nr = {
            "real": 0,
            "imaginary": 0
        }

        set_real(complex_nr, real)
        set_imaginary(complex_nr, im)

        return complex_nr

    if s[i] == '+' or s[i] == '-':
        real = int(n)

        if neg == True:
            real *= -1

    if s[i] == 'i':
        real = 0
        im = int(n)

        if neg == True:
            im *= -1

        complex_nr = {
            "real": 0,
            "imaginary": 0
        }

        set_real(complex_nr, real)
        set_imaginary(complex_nr, im)

        return complex_nr

    neg = False
    if s[i] == '-':
        neg = True

    i += 1
    if s[i] == 'i':
        im = 1

        if neg == True:
            im *= -1

        complex_nr = {
            "real": 0,
            "imaginary": 0
        }

        set_real(complex_nr, real)
        set_imaginary(complex_nr, im)

        return complex_nr

    n = ""
    while i < len(s) and (s[i] >= '0' and s[i] <= '9'):
        n += s[i]
        i += 1

    if s[i] == 'i':
        im = int(n)

        if neg == True:
            im *= -1

        complex_nr = {
            "real": 0,
            "imaginary": 0
        }

        set_real(complex_nr, real)
        set_imaginary(complex_nr, im)

        return complex_nr

def get_real(dict):
    return dict["real"]

def get_imaginary(dict):
    return dict["imaginary"]

def set_real(dict, val):
    dict["real"] = val

def set_imaginary(dict, val):
    dict["imaginary"] = val

def to_string(dict):
    if get_real(dict) == 0 and get_imaginary(dict) == 0:
        return "0"

    if get_real(dict) == 0 and get_imaginary(dict) != 0:
        if get_imaginary(dict) == 1:
            return "i"

        if get_imaginary(dict) == -1:
            return "-i"

        s = str(get_imaginary(dict)) + "i"
        return s

    if get_real(dict) != 0 and get_imaginary(dict) == 0:
        s = str(get_real(dict))
        return s

    if get_real(dict) != 0 and get_imaginary(dict) != 0:
        if get_imaginary(dict) == 1:
            s = str(get_real(dict)) + "+i"
            return s

        if get_imaginary(dict) == -1:
            s = str(get_real(dict)) + "-i"
            return s

        if get_imaginary(dict) > 0:
            s = str(get_real(dict)) + "+" + str(get_imaginary(dict)) + "i"

        if get_imaginary(dict) < 0:
            s = str(get_real(dict)) + str(get_imaginary(dict)) + "i"

        return s
"""
# List

def create_complex_nr(s: str):
    i = 0
    n = ""
    real = 0
    im = 0
    neg = False

    if s == "i":
        complex_nr = [0, 0]
        set_real(complex_nr, 0)
        set_imaginary(complex_nr, 1)

        return complex_nr

    if s == "-i":
        complex_nr = [0, 0]
        set_real(complex_nr, 0)
        set_imaginary(complex_nr, -1)

        return complex_nr

    if s[0] == '-':
        neg = True
        i += 1

    while i < len(s) and (s[i] >= '0' and s[i] <= '9'):
        n += s[i]
        i += 1

    if i == len(s):
        real = int(n)
        im = 0

        if neg == True:
            real *= -1

        complex_nr = [0, 0]
        set_real(complex_nr, real)
        set_imaginary(complex_nr, im)

        return complex_nr

    if s[i] == '+' or s[i] == '-':
        real = int(n)

        if neg == True:
            real *= -1

    if s[i] == 'i':
        real = 0
        im = int(n)

        if neg == True:
            im *= -1

        complex_nr = [0, 0]
        set_real(complex_nr, real)
        set_imaginary(complex_nr, im)

        return complex_nr

    neg = False
    if s[i] == '-':
        neg = True

    i += 1
    if s[i] == 'i':
        im = 1

        if neg == True:
            im *= -1

        complex_nr = [0, 0]
        set_real(complex_nr, real)
        set_imaginary(complex_nr, im)

        return complex_nr

    n = ""
    while i < len(s) and (s[i] >= '0' and s[i] <= '9'):
        n += s[i]
        i += 1

    if s[i] == 'i':
        im = int(n)

        if neg == True:
            im *= -1

        complex_nr = [0, 0]
        set_real(complex_nr, real)
        set_imaginary(complex_nr, im)

        return complex_nr

def get_real(list):
    return list[0]

def get_imaginary(list):
    return list[1]

def set_real(list, val):
    list[0] = val

def set_imaginary(list, val):
    list[1] = val

def to_string(list):
    if get_real(list) == 0 and get_imaginary(list) == 0:
        return "0"

    if get_real(list) == 0 and get_imaginary(list) != 0:
        if get_imaginary(list) == 1:
            return "i"

        if get_imaginary(list) == -1:
            return "-i"

        s = str(get_imaginary(list)) + "i"
        return s

    if get_real(list) != 0 and get_imaginary(list) == 0:
        s = str(get_real(list))
        return s

    if get_real(list) != 0 and get_imaginary(list) != 0:
        if get_imaginary(list) == 1:
            s = str(get_real(list)) + "+i"
            return s

        if get_imaginary(list) == -1:
            s = str(get_real(list)) + "-i"
            return s

        if get_imaginary(list) > 0:
            s = str(get_real(list)) + "+" + str(get_imaginary(list)) + "i"

        if get_imaginary(list) < 0:
            s = str(get_real(list)) + str(get_imaginary(list)) + "i"

        return s

# UI

def read_the_numbers(l: list):
    nr = input("Your numbers will be: ").split(", ")

    for i in nr:
        aux = ""
        for j in range(len(i)):
            if i[j] != " ":
                aux += i[j]

        x = create_complex_nr(aux)
        l.append(x)

def display_the_list(l: list):
    for i in l:
        print(i)

def display_the_subarray(l: list):
    """
    This function displays the results for the first problem
    :param l: the list given by the user
    :return:
    """
    arr = []

    subarray_len = longest_subarray(l, arr)
    print("The legth of the subarray is:", subarray_len)
    print("The subarray is:", arr)


def display_the_subseq(l: list):
    """
    This function displays the results for the second problem
    :param l: the list given by the user
    :return:
    """
    s = []
    m = []
    seq = []
    for i in l:
        m.append(number_modulus(i))

    seq_length = longest_increasing_subseq(m, s, seq)

    print("The length of the subsequence is:", seq_length)
    print("The subsequence is: ", end="")
    for i in range(len(seq) - 1, -1, -1):
        print(l[seq[i]], end=" ")

    print("\n", end="")


def create_menu(l: list):
    print("Please choose one of the following options:")
    while True:
        print("1) Read a list with complex numbers")
        print("2) Display the list")
        print("3) Display the results of the subproblems")
        print("4) Exit")

        cmd = input("-> ")

        if cmd == "1":
            read_the_numbers(l)
        elif cmd == "2":
            display_the_list(l)
        elif cmd == "3":
            display_the_subarray(l)
            display_the_subseq(l)
        elif cmd == "4":
            break
        else:
            print("Bad command!")



# Main
l = []

initial_cases(l)
create_menu(l)