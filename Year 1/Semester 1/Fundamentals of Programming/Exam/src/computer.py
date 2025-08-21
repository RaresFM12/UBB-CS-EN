import random
from copy import deepcopy

from numpy.ma.core import choose


class Computer:
    def __init__(self):
        pass

    def choose_random_coordinates(self, board):
        all_pos = []
        for i in range(6):
            for j in range(6):
                if board.board[i][j] == ' ':
                    all_pos.append([i, j])

        coord = random.choice(all_pos)
        sym = random.choice(["O", "X"])
        return coord[0], coord[1], sym

    def place_random_symbol(self, board):
        x, y, s = self.choose_random_coordinates(board)
        board.board[x][y] = s







