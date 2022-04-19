from random import randint
from copy import copy
from src.domain.board import LogisticsException
from src.domain.domain import Ship
from src.domain.validators import GameException, PositionValidator


class Computer:
    def __init__(self, intelligence):
        self.__intelligence = intelligence

    @staticmethod
    def ships_setting(board):
        # The computer's ships will be set randomly
        ships = {"Carrier": 5, "Battleship": 4, "Cruiser": 3, "Submarine": 3, "Destroyer": 2}

        for ship_name in ships:
            while True:
                try:
                    length = ships[ship_name]
                    x = randint(0, 9)
                    y = randint(0, 9)
                    start_pos = [x, y]
                    direction = randint(0, 1)  # 0 for horizontal, 1 for vertical
                    if direction == 0:
                        end_pos = [x + length - 1, y]
                    else:
                        end_pos = [x, y + length - 1]
                    PositionValidator().validate(end_pos[0], end_pos[1])
                    ship = Ship(start_pos, end_pos)
                    board.set_ship(ship, 1)
                except LogisticsException:
                    pass
                except GameException:
                    pass
                except IndexError:
                    pass
                else:
                    break

    def move_computer(self, board=None):
        if self.__intelligence == "dumb":
            return self.random_move_computer()
        elif self.__intelligence == "smart":
            return self.move_on_diagonals(board)

    @staticmethod
    def random_move_computer():
        # this ai is dumb, it makes random moves
        x = randint(0, 9)
        y = randint(0, 9)
        return x, y

    x, y = 0, 0
    aux_x, aux_y = 0, 0
    hit = False
    sunk = True

    def move_on_diagonals(self, board):
        # the computer will hit only on diagonals (like on a chess board), as this means it will cover more ground,
        # more efficiently
        # if a ship has been found, it will start hitting the adjacent squares, until the ship has been sunk
        if board.get_element(self.x, self.y) == 3:
            self.hit = True
        elif board.get_element(self.x, self.y) == 5:
            self.sunk = True
            self.hit = False
        if self.hit is False or self.sunk is True:
            if self.sunk is True:
                # if last time we found a ship and sunk it, we return to our initial search positions, which we store in
                # aux_x and aux_y
                self.sunk = False
                self.x, self.y = self.aux_x, self.aux_y
            if self.x == 0 and self.y == 0:
                self.y += 1
            else:
                while True:
                    # here we get the next search positions
                    if self.y == 9:
                        self.x += 1
                        self.y = 0
                    elif self.y == 8:
                        self.x += 1
                        self.y = 1
                    else:
                        self.y += 2
                    if board.get_element(self.x, self.y) == 0:
                        break
            self.aux_x, self.aux_y = copy(self.x), copy(self.y)
            return self.x, self.y

        elif self.hit is True and self.sunk is False:
            # the first position we should check is the left side, then up, then down and lastly, right
            if self.y - 1 >= 0 and board.get_element(self.x, self.y - 1) == 0:
                return self.x, self.y - 1
            elif self.x - 1 >= 0 and board.get_element(self.x - 1, self.y) == 0:
                return self.x - 1, self.y
            else:
                # there's 3 possibilities: vertical ship, horizontal ship or we still don't know
                if self.x == board.hits[-1][0]:
                    # this means it's a vertical ship
                    self.y += 1
                    return self.x, self.y
                elif self.x == board.hits[-1][0] - 1:
                    # this means it's a horizontal ship
                    self.x += 1
                    return self.x, self.y
                else:
                    # we check to see in which direction we can go: down or right
                    if self.x + 1 <= 9:
                        return self.x + 1, self.y
                    elif self.y + 1 <= 9:
                        return self.x, self.y + 1
