from src.computer import Computer
from src.service import Player


class UI:
    def __init__(self):
        self.__player = Player()
        self.__computer = Computer()

    def run_ui(self):
        b = self.__player.get_board()
        print(b)

        while True:
            cmd = input("Order's move: ")
            cmd = cmd.split(" ")

            if len(cmd) != 3:
                print("Bad command!")
            else:
                x = cmd[0]
                y = cmd[1]
                s = cmd[2]

                try:
                    self.__player.place_symbol(x, y, s)

                    if self.__player.winning_board() == True:
                        self.order_wins()
                        break

                    if self.__player.full_board() == True:
                        self.chaos_wins()
                        break

                    self.__computer.place_random_symbol(self.__player.get_board())

                    if self.__player.winning_board() == True:
                        self.order_wins()
                        break

                    if self.__player.full_board() == True:
                        self.chaos_wins()
                        break

                    b = self.__player.get_board()
                    print(b)

                except ValueError as ve:
                    print(ve)

    def order_wins(self):
        b = self.__player.get_board()
        print(b)
        print("Order wins! The game is over!")

    def chaos_wins(self):
        b = self.__player.get_board()
        print(b)
        print("Chaos wins! The game is over!")
