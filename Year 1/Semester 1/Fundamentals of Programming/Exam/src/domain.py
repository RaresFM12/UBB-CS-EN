import texttable

N = 6
C = 5

class Board:
    def __init__(self):
        self.__data = []
        for i in range(N):
            self.__data.append([' '] * N)

    @property
    def board(self):
        return self.__data

    def __str__(self):
        t = texttable.Texttable()
        for i in range(N):
            t.add_row(self.__data[i])

        return t.draw()


