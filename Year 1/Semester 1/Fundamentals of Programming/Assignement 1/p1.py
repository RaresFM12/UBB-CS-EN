# Solve the problem from the first set here

def find_all_digits(x, fr):
    while x != 0:
        fr[x % 10] += 1
        x //= 10            #   //= -> is used to get rid of the last digit

def new_number(n, fr) -> int:
    n = 0
    for i in range(1, 10):  # in case the initial number has a zero
        if fr[i] != 0:
            n = i
            fr[i] -= 1
            break

    for i in range(0, 10):
        while fr[i] != 0:
            n = n * 10 + i
            fr[i] -= 1

    return n

n = int(input("The initial number is: "))
fr = []
for i in range(0, 10):
    fr.append(0)

find_all_digits(n, fr)
m = new_number(n, fr)
print("The final number is: ", m)
