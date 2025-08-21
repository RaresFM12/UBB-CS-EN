import unittest

from src.domain.board import Board
from src.services.ai import AI


class TestAI(unittest.TestCase):
    def setUp(self):
        self.__board = Board()
        self.__ai = AI(6)

    def tearDown(self):
        pass

    def test_winning_move(self):
        for i in range(4):
            self.__ai.drop_piece(self.__board, 1, 1)

        for i in range(2, 7):
            self.__ai.drop_piece(self.__board, i, 2)

        self.assertEqual(self.__ai.winning_move(self.__board, 1), True)
        self.assertEqual(self.__ai.winning_move(self.__board, 2), True)

    def test_drop_piece(self):
        self.__ai.drop_piece(self.__board, 1, 1)
        self.assertEqual(self.__board.board[0][1], 1)

    def test_evaluate_window(self):
        for i in range(3):
            self.__ai.drop_piece(self.__board, 1, 2)

        window = [self.__board.board[0][1], self.__board.board[1][1], self.__board.board[2][1],
                  self.__board.board[3][1]]
        self.assertEqual(self.__ai.evaluate_window(window, 2), 10)

        for i in range(3):
            self.__ai.drop_piece(self.__board, 2, 1)

        window = [self.__board.board[0][2], self.__board.board[1][2], self.__board.board[2][2],
                  self.__board.board[3][2]]
        self.assertEqual(self.__ai.evaluate_window(window, 2), -8)

    def test_score_position(self):
        for i in range(3):
            self.__ai.drop_piece(self.__board, 1, 2)

        for i in range(3):
            self.__ai.drop_piece(self.__board, 2, 1)

        self.assertEqual(self.__ai.score_position(self.__board, 2), 4)

    def test_is_valid_location(self):
        self.__ai.drop_piece(self.__board, 1, 1)
        value = self.__ai.is_valid_location(self.__board, 1)
        self.assertEqual(value, True)

        for i in range(5):
            self.__ai.drop_piece(self.__board, 1, 1)

        value = self.__ai.is_valid_location(self.__board, 1)
        self.assertEqual(value, False)

    def test_get_valid_columns(self):
        for i in range(4):
            for j in range(6):
                self.__ai.drop_piece(self.__board, i, 1)

        col = self.__ai.get_valid_columns(self.__board)
        self.assertEqual(col, [4, 5, 6])

    def test_terminal(self):
        for i in range(3):
            self.__ai.drop_piece(self.__board, 1, 1)

        self.assertEqual(self.__ai.terminal(self.__board), False)

        self.__ai.drop_piece(self.__board, 1, 1)
        self.assertEqual(self.__ai.terminal(self.__board), True)

    def test_minimax(self):
        for i in range(3):
            self.__ai.drop_piece(self.__board, 3, 1)

        col = self.__ai.minimax(self.__board, 6, -100000, 100000, 2)[0]
        self.__ai.drop_piece(self.__board, col, 2)
        self.assertEqual(self.__board.board[3][3], 2)

        for i in range(3):
            self.__ai.drop_piece(self.__board, 4, 2)

        col = self.__ai.minimax(self.__board, 6, -100000, 100000, 2)[0]
        self.__ai.drop_piece(self.__board, col, 2)
        self.assertEqual(self.__board.board[3][4], 2)

    def test_get_next_open_row(self):
        self.__ai.drop_piece(self.__board, 1, 1)
        row = self.__ai.get_next_open_row(self.__board, 1)
        self.assertEqual(row, 1)

        for i in range(5):
            self.__ai.drop_piece(self.__board, 1, 1)

        row = self.__ai.get_next_open_row(self.__board, 1)
        self.assertEqual(row, -1)

if __name__ == "__main__":
    unittest.main()