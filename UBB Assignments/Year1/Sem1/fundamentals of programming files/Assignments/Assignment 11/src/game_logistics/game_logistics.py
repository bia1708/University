from enum import Enum

from src.domain.board import Board
from src.domain.domain import Ship
from src.domain.validators import ShipValidator, PositionValidator


class GameStatus(Enum):
    ONGOING = 0
    DRAW = 1
    LOST = 2
    WON = 3


class Game:
    def __init__(self, ai):
        self.__player_board = Board()
        self.__player_strategy_board = Board()
        self.__computer_board = Board()
        self.__computer_strategy_board = Board()
        self.__ai = ai
        self.__round_counter = 1

    def game_status(self):
        if self.__player_board.defeated() is True and self.__computer_board.defeated() is True:
            return GameStatus.DRAW.value
        if self.__player_board.defeated() is True:
            return GameStatus.LOST.value
        if self.__computer_board.defeated() is True:
            return GameStatus.WON.value
        return GameStatus.ONGOING.value

    def set_ship(self, start_pos, end_pos, length):
        ShipValidator().validate(start_pos, end_pos, length)
        ship = Ship(start_pos, end_pos)
        self.__player_board.set_ship(ship, 1)

    def computer_ships(self):
        self.__ai.ships_setting(self.__computer_board)

    def random_ships(self):
        self.__ai.ships_setting(self.__player_board)

    def move_player(self, x, y):
        # on the player's strategy board, the correct hits will be '*'(3) and the missed hits will be '0'(4)
        # 5 will be returned if the ship you hit has sunk
        PositionValidator().validate(x, y)
        if self.__computer_board.get_element(x, y) == 1:
            # if there is a ship there, we set it to damaged(2)
            ship = self.__computer_board.get_ship(x, y)
            self.__computer_board.set_element(x, y, 2)
            self.__player_strategy_board.set_element(x, y, 3)

            if self.__computer_board.check_ship_integrity(ship) is True:
                return 5
            return 3
        else:
            self.__player_strategy_board.set_element(x, y, 4)
            return 4

    def move_computer(self):
        x, y = self.__ai.move_computer(self.__computer_strategy_board)
        if self.__player_board.get_element(x, y) == 1:
            ship = self.__player_board.get_ship(x, y)
            self.__player_board.set_element(x, y, 2)
            self.__computer_strategy_board.set_element(x, y, 3)

            if self.__player_board.check_ship_integrity(ship) is True:
                new_ship = Ship(ship.starting_pos, ship.ending_pos)
                self.__computer_strategy_board.set_found_ship(new_ship, 5)
                return 5
            return 3
        else:
            self.__computer_strategy_board.set_element(x, y, 4)
            return 4

    def get_board(self, type):
        if type == "player":
            return self.__player_board
        elif type == "strategy":
            return self.__player_strategy_board
        elif type == "computer":
            return self.__computer_board
        elif type == "computer_strategy":
            return self.__computer_strategy_board

    def increase_round(self):
        self.__round_counter += 1

    @property
    def rounds(self):
        return self.__round_counter
