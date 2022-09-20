from src.domain.validators import GameException
from src.domain.board import LogisticsException

"""
The types of ships and their sizes:
Carrier	    5
Battleship	4
Cruiser 	3
Submarine	3
Destroyer	2
"""


class UI:
    def __init__(self, game):
        self.__game = game

    @staticmethod
    def transform_position(position):
        if position[0].isdigit():
            if len(position) == 2:
                if int(position[0]) == 0 or position[1] not in "ABCDEFGHIJ":
                    raise GameException("Please enter a valid position!")
                else:
                    position = [int(position[0]) - 1, int(ord(position[1]) - 65)]
            else:
                if int(position[1]) > 0 or int(position[0]) > 1 or position[2] not in "ABCDEFGHIJ":
                    raise GameException("Please enter a valid position!")
                else:
                    position = [9, int(ord(position[2]) - 65)]
        else:
            if len(position) == 2:
                if int(position[1]) == 0 or position[0] not in "ABCDEFGHIJ":
                    raise GameException("Please enter a valid position!")
                else:
                    position = [int(position[1]) - 1, int(ord(position[0]) - 65)]
            else:
                if int(position[2]) > 0 or int(position[1]) > 1 or position[0] not in "ABCDEFGHIJ":
                    raise GameException("Please enter a valid position!")
                position = [9, int(ord(position[0]) - 65)]
        return position

    def ui_set_ship(self, length):
        start_pos = input("Starting position: ")
        start_pos = self.transform_position(start_pos)

        end_pos = input("Ending position: ")
        end_pos = self.transform_position(end_pos)

        self.__game.set_ship(start_pos, end_pos, length)

    def create_ships(self):
        print("You have 5 ships at your disposal: a carrier(5 tiles), a battleship(4 tiles), a cruiser(3 tiles), a "
              "submarine(3 tiles) and a destroyer(2 tiles).\nPlease arrange your ships on the board!\n")

        ships = {"Carrier": 5, "Battleship": 4, "Cruiser": 3, "Submarine": 3, "Destroyer": 2}

        for ship_name in ships:
            print(f"Place your {ship_name}({ships[ship_name]} tiles):")
            while True:
                try:
                    self.ui_set_ship(ships[ship_name])
                except GameException as ge:
                    print(ge)
                except LogisticsException as le:
                    print(le)
                except IndexError:
                    print("Please enter the position correctly!")
                else:
                    break
            print(self.__game.get_board("player"))

    def ui_move_player(self):
        turn = True
        while turn is True:
            try:
                attack_pos = input("Position to attack: ")
                attack_pos = self.transform_position(attack_pos)
                result = self.__game.move_player(attack_pos[0], attack_pos[1])
                if result == 3:
                    print("Nice hit!")
                elif result == 4:
                    print("You missed!")
                elif result == 5:
                    print("Ship destroyed! Good job!")
                turn = False
            except GameException as ge:
                print(ge)

    def startup(self):
        print("Welcome to BattleShip!\n")

        # ship placement for the computer
        self.__game.computer_ships()
        # print(self.__game.get_board("computer"))

        # ship placement for the player
        option = input("Do you want to manually place the ships?(yes/no)\n")
        if option == "yes":
            print(self.__game.get_board("player"))
            self.create_ships()
        else:
            self.__game.random_ships()
            print("Your ships:")
            print(self.__game.get_board("player"))

        turn_option = input("Would you like to be first?(yes/no)\n")

        while self.__game.game_status() == 0:
            print(f"\nRound {self.__game.rounds}!")
            if turn_option == "yes":

                print("Strategy board:")
                print(self.__game.get_board("strategy"))
                self.ui_move_player()

                self.__game.move_computer()
                print("Your board after the computer moved:")
                print(self.__game.get_board("player"))
            else:
                self.__game.move_computer()
                print("Your board after the computer moved:")
                print(self.__game.get_board("player"))

                print("Strategy board:")
                print(self.__game.get_board("strategy"))
                self.ui_move_player()
            self.__game.increase_round()

        print (self.__game.game_status)
        if self.__game.game_status == 1:
            print("It's a draw!")
        elif self.__game.game_status == 2:
            print("You lost!")
        else:
            print("YOU WIN!!!")
