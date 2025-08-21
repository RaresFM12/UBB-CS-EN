from domain import Board


class Player:
    def __init__(self):
        self.__board = Board()
        self.__over = False

    def get_board(self):
        return self.__board

    def get_over(self):
        return self.__over

    def is_over(self, i, j):
        if self.__board.board[i][j] == '+':
            return True

        return False

    def validate_move(self, x, y, s):
        try:
            x = int(x)
            y = int(y)
        except:
            raise ValueError("This coordinates have to be integers!")

        if s != "O" and s != "X":
            raise ValueError("This is not a correct symbol!")

        if (x < 1 or x > 6) or (y < 1 or y > 6):
            raise ValueError("This coordinates are not good!")

    def place_symbol(self, x, y, s):
        self.validate_move(x, y, s)
        x = int(x) - 1
        y = int(y) - 1
        self.__board.board[x][y] = s

    def full_board(self):
        for i in range(6):
            for j in range(6):
                if self.__board.board[i][j] == " ":
                    return False

        return True

    def winning_board(self):
        # Checks lines
        for i in range(6):
            for j in range(2):
                if self.__board.board[i][j] != " ":
                    if self.__board.board[i][j] == self.__board.board[i][j + 1]:
                        if self.__board.board[i][j] == self.__board.board[i][j + 2]:
                            if self.__board.board[i][j] == self.__board.board[i][j + 3]:
                                if self.__board.board[i][j] == self.__board.board[i][j + 4]:
                                    return True
        # Checks columns
        for i in range(2):
            for j in range(6):
                if self.__board.board[i][j] != " ":
                    if self.__board.board[i][j] == self.__board.board[i + 1][j]:
                        if self.__board.board[i][j] == self.__board.board[i + 2][j]:
                            if self.__board.board[i][j] == self.__board.board[i + 3][j]:
                                if self.__board.board[i][j] == self.__board.board[i + 4][j]:
                                    return True
        # Checks diagonal (from left to right)
        for i in range(2):
            for j in range(2):
                if self.__board.board[i][j] != " ":
                    if self.__board.board[i][j] == self.__board.board[i + 1][j + 1]:
                        if self.__board.board[i][j] == self.__board.board[i + 2][j + 2]:
                            if self.__board.board[i][j] == self.__board.board[i + 3][j + 3]:
                                if self.__board.board[i][j] == self.__board.board[i + 4][j + 4]:
                                    return True
        # Checks diagonal (from right to left)
        for i in range(2):
            for j in range(5, 3, -1):
                if self.__board.board[i][j] != " ":
                    if self.__board.board[i][j] == self.__board.board[i + 1][j - 1]:
                        if self.__board.board[i][j] == self.__board.board[i + 2][j - 2]:
                            if self.__board.board[i][j] == self.__board.board[i + 3][j - 3]:
                                if self.__board.board[i][j] == self.__board.board[i + 4][j - 4]:
                                    return True
        return False