import copy
import math
import random


from src.domain.board import HEIGHT, WIDTH


class AI:
    def __init__(self, depth):
        self.__depth = depth
        self.__columns_array = [3, 4, 2, 1, 5, 0, 6]    # in this order because there are the bigger scores
        self.__AI = 2
        self.__HUMAN = 1
        self.__MAX_VALUE = 100000

    def set_depth(self, depth):
        self.__depth = depth

    def winning_move(self, board, player):
        """
        Checks if one of the players won
        :param board: the board
        :param player: the player
        :return: True if the player won, False otherwise
        """
        # Checks for horizontal locations for win
        for row in range(HEIGHT):
            for column in range(WIDTH - 3):
                if board.board[row][column] == board.board[row][column + 1] == board.board[row][column + 2] == \
                        board.board[row][column + 3] == player:
                    return True

        for row in range(HEIGHT - 3):
            for column in range(WIDTH):
                # Checks for vertical locations for win
                if board.board[row][column] == board.board[row + 1][column] == board.board[row + 2][column] == \
                        board.board[row + 3][column] == player:
                    return True

            for column in range(WIDTH - 1, 2, -1):
                # Checks on the secondary diagonal for a win location
                if board.board[row][column] == board.board[row + 1][column - 1] == board.board[row + 2][column - 2] == \
                        board.board[row + 3][column - 3] == player:
                    return True

            for column in range(WIDTH - 3):
                # Checks on the main diagonal for a win location
                if board.board[row][column] == board.board[row + 1][column + 1] == board.board[row + 2][column + 2] == \
                        board.board[row + 3][column + 3] == player:
                    return True

        return False

    def drop_piece(self, board, column, player):
        """
        Drops a token on the first row available for a specific player on a given column
        :param board: the board
        :param column: the given column
        :param player: the player
        :return: None
        """
        board.board[self.get_next_open_row(board, column)][column] = player

    def evaluate_window(self, window, piece):
        """
        Evaluates the score for a specific window(interval)
        :param window: the interval with tokens
        :param piece: whose pieces are
        :return: the score of the window
        """
        score = 0
        opp_piece = self.__HUMAN
        if piece == self.__HUMAN:
            opp_piece = self.__AI


        if window.count(piece) == 3 and window.count(0) == 1:
            score += 10
        elif window.count(piece) == 2 and window.count(0) == 2:
            score += 2

        if window.count(opp_piece) == 3 and window.count(0) == 1:
            score -= 8

        return score

    def score_position(self, board, piece):
        """
        Evaluates the score for the current state of the board
        :param board: the current state of the board
        :param piece: whose pieces are
        :return: the score of the current state
        """
        score = 0

        # Score Horizontal
        for r in range(HEIGHT):
            row_array = [int(i) for i in list(board.board[r, :])]
            for c in range(WIDTH - 3):
                window = row_array[c:c + 4]
                score += self.evaluate_window(window, piece)

        # Score Vertical
        for c in range(WIDTH):
            col_array = [int(i) for i in list(board.board[:, c])]
            for r in range(HEIGHT - 3):
                window = col_array[r:r + 4]
                score += self.evaluate_window(window, piece)

        # Score main diagonal
        for r in range(HEIGHT - 3):
            for c in range(WIDTH - 3):
                window = [board.board[r + i][c + i] for i in range(4)]
                score += self.evaluate_window(window, piece)

        # Score secondary diagonal
        for r in range(HEIGHT - 3):
            for c in range(WIDTH - 3):
                window = [board.board[r + 3 - i][c + i] for i in range(4)]
                score += self.evaluate_window(window, piece)

        return score

    def is_valid_location(self, board, column):
        """
        Checks if a specific column is available
        :param board: the board
        :param column: the specific column
        :return: True if the column is available, False otherwise
        """
        return board.board[HEIGHT - 1][column] == 0

    def get_valid_columns(self, board):
        """
        Checks which of the columns are available
        :param board: the board
        :return: list of all the available columns
        """
        return [int(col) for col in self.__columns_array if self.is_valid_location(board, col)]

    def terminal(self, board):
        """
        Checks if the game has ended in some way(win one of the players, it's a tie)
        :param board: the board
        :return: True if one of the players won or if it's a draw, False otherwise
        """
        return self.winning_move(board, self.__AI) or self.winning_move(board, self.__HUMAN) or \
                len(self.get_valid_columns(board)) == 0

    def minimax(self, board, depth, alpha, beta, maxplayer):
        """
        This function implements the minimax algorithm to find the best location for the token.
        This algorithm uses alpha-beta pruning.
        :param board: the current state of the board
        :param depth: the depth of the tree
        :param alpha: the best score so far for the maximizing player
        :param beta: the best score so far for the minimizing player
        :param maxplayer: maximizing player
        :return: the best column for the token, and the value of the score for the best possibility
        """
        valid_locations = self.get_valid_columns(board)
        is_terminal = self.terminal(board)

        if depth == 0 or is_terminal:
            if is_terminal:
                if self.winning_move(board, self.__AI):
                    return None, self.__MAX_VALUE

                elif self.winning_move(board, self.__HUMAN):
                    return None, -self.__MAX_VALUE

                else:  # Game is over, no more valid moves
                    return None, 0
            else:  # Depth is zero
                return None, self.score_position(board, self.__AI)  # we return the score of the current state

        if maxplayer:
            value = -math.inf
            column = random.choice(valid_locations)
            for col in valid_locations:
                b_copy = copy.deepcopy(board)
                self.drop_piece(b_copy, col, self.__AI)
                new_score = self.minimax(b_copy, depth - 1, alpha, beta, False)[1]

                # The maximizing player always chooses the largest score
                if new_score > value:
                    value = new_score
                    column = col
                alpha = max(alpha, value)
                if alpha >= beta:   # we don't go on the other branches
                    break
            return column, value

        else:  # Minimizing player
            value = math.inf
            column = random.choice(valid_locations)
            for col in valid_locations:
                b_copy = copy.deepcopy(board)
                self.drop_piece(b_copy, col, self.__HUMAN)
                new_score = self.minimax(b_copy, depth - 1, alpha, beta, True)[1]

                # The minimizing player always chooses the smallest score
                if new_score < value:
                    value = new_score
                    column = col
                beta = min(beta, value)
                if alpha >= beta:    # we don't go on the other branches
                    break
            return column, value

    def get_next_open_row(self, board, column):
        """
        Returns the row, from a specific column, on which we can put a token
        :param board: the board
        :param column: the given column
        :return: the row, or 0 if we can't find one
        """
        for row in range(HEIGHT):
            if board.board[row][column] == 0:
                return row

        return -1



