from src.controller.controller import GameException
from src.domain.validator import ValueException


class Console:
    def __init__(self, controller):
        self.__controller = controller

    @staticmethod
    def print_menu():
        print("Welcome to Order and Chaos!")

    def player_move(self):
        print("Your move:")
        choice = True
        while choice is True:
            try:
                x_pos = int(input("X coordinate: ")) - 1
                y_pos = int(input("Y coordinate: ")) - 1
                symbol = input("Symbol chosen: ").lower()
                self.__controller.place_symbol(x_pos, y_pos, symbol)
                choice = False
            except ValueException as ve:
                print(ve)
            except ValueError:
                print("Please enter a valid position!")
            except GameException as ge:
                print(ge)

    def computer_move(self):
        self.__controller.computer_move()

    def run_game(self):
        self.print_menu()
        game_round = 1
        game_status = "ongoing"

        while game_status != "over":
            print(f"\nRound {game_round}!\n")
            game_round += 1
            print(self.__controller.get_board())
            print("\n")

            self.player_move()
            if game_round > 4:
                game_status = self.__controller.check_game_status()
            if game_status == "over":
                print(self.__controller.get_board())
                print("Player WON!")
                return False
            if game_status == "computer_won":
                print(self.__controller.get_board())
                print("Computer WON!")
                return False
            self.computer_move()
            if game_round > 4:
                game_status = self.__controller.check_game_status()
            if game_status == "over":
                print(self.__controller.get_board())
                print("Computer WON!")