import math

from src.services.ai import AI
from src.services.game import Game


class UI:
    def __init__(self):
        self.__game = Game()
        self.__ai = AI(6)
        self.__depth = 6
        self.__tokens = ["\U000026aa", "\U0001f534", "\U0001f7e1"]    # in unicode

    def print_board(self):
        board = self.__game.get_board()
        for row in board:
            for column in row:
                print(self.__tokens[column], end=" ")
            print()

    def run(self):
        print("Welcome to Connect Four!!!")
        print("1. Play against a friend")
        print("2. Play against the computer")

        cmd = input("-> ")

        if cmd == "1":
            print("You chose to play against a friend!")
            self.print_board()
            self.play_against_a_friend()
        elif cmd == "2":
            print("You chose to play against the computer!")
            self.print_board()
            self.play_against_computer()
        else:
            print("Bad command!")
            self.run()

    def play_against_computer(self):
        while not self.__game.game_over:
            self.player_turn()
            if not self.__game.game_over:
                self.computer_turn()

    def computer_turn(self):
        print("Computer's turn!")
        ai_col = self.__ai.minimax(self.__game.board, self.__depth, -math.inf, math.inf, True)[0]
        ai_row = self.__game.drop_piece(ai_col)[0]
        self.print_board()

        if self.__game.winning_move(ai_col, ai_row):
            print("AI won!")

        if self.__game.is_draw():
            print("Draw!")

    def play_against_a_friend(self):
        while not self.__game.game_over:
            self.player_turn()
            if not self.__game.game_over:
                self.player_turn()

    def player_turn(self):
        column = input("Player " + str(self.__game.turn + 1) + " make your selection(1 - 7): ")

        try:
            column = int(column) - 1

            if self.__game.is_valid_column(column):
                win = self.__game.drop_piece(column)[1]

                self.print_board()
                if win:
                    player = self.__game.turn
                    if player == 0:
                        player = 2

                    print("Player " + str(player) + " wins!")
                elif self.__game.is_draw():
                    print("It's a draw!")

            else:
                print("Invalid column!")
                self.player_turn()
        except:
            print("The column must be a number between 1 - 7!!!")
            self.player_turn()

