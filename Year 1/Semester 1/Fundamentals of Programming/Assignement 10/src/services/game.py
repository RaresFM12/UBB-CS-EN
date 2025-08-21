from src.domain.board import Board, HEIGHT, WIDTH
import numpy as np

class Game:
    def __init__(self):
        self.__board = Board()
        self.__game_over = False
        self.__turn = 0

    @property
    def board(self):
        return self.__board

    @property
    def game_over(self):
        return self.__game_over

    @game_over.setter
    def game_over(self, over):
        self.__game_over = over

    @property
    def turn(self):
        return self.__turn

    @turn.setter
    def turn(self, value):
        self.__turn = value

    def get_board(self):
        """
        Transfers the board in his current state
        :return: the board in its current state
        """
        return np.flip(self.__board.board, 0)

    def change_turn(self):
        """
        Changes the turn
        :return: None
        """
        self.__turn = (self.turn + 1) % 2

    def is_valid_column(self, column):
        """
        Returns True is this is a valid column or else it returns False
        :param column: the specific column
        :return: True or False
        """
        if column >= 0 and column < WIDTH:
            if self.__board.board[HEIGHT - 1][column] == 0:
                return True

        return False

    def drop_piece(self, column):
        """
        Drops a token on the first row available from a specific column
        :param column: the column given by the player
        :return: True if it's a winning move, False otherwise
        """
        row = self.get_next_open_row(column)

        if row != -1:
            self.__board.board[row, column] = self.turn + 1
            self.change_turn()
            return row, self.winning_move(column, row)

        return row, False


    def get_next_open_row(self, column):
        """
        Returns the row, from a specific column, on which we can put a token
        :param column: the column on which the player wants to place his token
        :return: the row, or -1 if we can't
        """
        for row in range(HEIGHT):
            if self.__board.board[row, column] == 0:
                return row

        return -1      # the column is full

    def is_draw(self):
        """
        Checks if the game is a draw
        :return: True if it's a draw, False otherwise
        """
        if np.count_nonzero(self.__board.board) == WIDTH * HEIGHT:
            self.__game_over = True
            return True

        return False

    def winning_move(self, column, row):
        """
        Checks if the last move was a winning one
        :param column: the column where the last move was made
        :param row: the row where the last move was made
        :return: True if it's a winning move and False otherwise
        """

        if row == -1:
            return False

        # if there are equal elements vertically
        if row >= 3 and self.__board.board[row][column] == self.__board.board[row - 1][column] == self.__board.board[row - 2][
            column] == self.__board.board[row - 3][column]:
            self.__game_over = True
            return True

        for gap in range(4):
            top_vertical = row - gap
            top_horizontal = column + gap

            if top_horizontal < WIDTH and top_horizontal - 3 >= 0:
                # if there are equal elements horizontally, with the new element in the interior of the interval
                if self.__board.board[row][top_horizontal] == self.__board.board[row][top_horizontal - 1] == self.__board.board[row][
                    top_horizontal - 2] == self.__board.board[row][top_horizontal - 3]:
                    self.__game_over = True
                    return True

                # if there are equal elements on the main diagonal, with the new element in the interior of the interval
                if top_vertical >= 0 and top_vertical + 3 < HEIGHT:
                    if self.__board.board[top_vertical][top_horizontal] == self.__board.board[top_vertical + 1][top_horizontal - 1] == \
                        self.__board.board[top_vertical + 2][top_horizontal - 2] == self.__board.board[top_vertical + 3][top_horizontal - 3]:
                        self.__game_over = True
                        return True

            top_horizontal = column - gap

            # if there are equal elements on the secondary diagonal, with the new element in the interior of the interval
            if top_horizontal >= 0 and top_horizontal + 3 < WIDTH:
                if top_vertical >= 0 and top_vertical + 3 < HEIGHT:
                    if self.__board.board[top_vertical][top_horizontal] == self.__board.board[top_vertical + 1][top_horizontal + 1] == \
                        self.__board.board[top_vertical + 2][top_horizontal + 2] == self.__board.board[top_vertical + 3][top_horizontal + 3]:
                        self.__game_over = True
                        return True

        return False

