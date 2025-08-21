import unittest

from src.services.game import Game


class TestGame(unittest.TestCase):
    def setUp(self):
        self.__service = Game()

    def tearDown(self):
        pass

    def test_change_turn(self):
        self.__service.turn = 1
        self.__service.change_turn()
        self.assertEqual(self.__service.turn, 0)

    def test_is_valid_column(self):
        self.__service.drop_piece(1)
        value = self.__service.is_valid_column(1)
        self.assertEqual(value, True)

        for i in range(5):
            self.__service.drop_piece(1)

        value = self.__service.is_valid_column(1)
        self.assertEqual(value, False)

    def test_drop_piece(self):
        row = self.__service.drop_piece(1)[0]
        self.assertEqual(row, 0)
        row = self.__service.drop_piece(1)[0]
        self.assertEqual(row, 1)

    def test_get_next_open_row(self):
        self.__service.drop_piece(1)
        row = self.__service.get_next_open_row(1)
        self.assertEqual(row, 1)

        for i in range(5):
            self.__service.drop_piece(1)

        row = self.__service.get_next_open_row(1)
        self.assertEqual(row, -1)

    def test_is_draw(self):
        self.assertEqual(self.__service.is_draw(), False)

        for i in range(7):
            for j in range(6):
                self.__service.drop_piece(i)

        self.assertEqual(self.__service.is_draw(), True)

    def test_winning_move(self):
        self.__service.drop_piece(1)
        self.__service.drop_piece(2)
        self.__service.drop_piece(1)
        self.__service.drop_piece(3)
        self.__service.drop_piece(1)
        self.__service.drop_piece(4)
        self.__service.drop_piece(1)
        self.__service.drop_piece(5)
        self.assertEqual(self.__service.winning_move(1, 3), True)
        self.assertEqual(self.__service.winning_move(5, 0), True)


if __name__ == "__main__":
    unittest.main()