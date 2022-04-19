
class LogisticsException(Exception):
    pass


class Board:
    def __init__(self):
        self.__board = [[0] * 10, [0] * 10, [0] * 10, [0] * 10, [0] * 10, [0] * 10, [0] * 10, [0] * 10, [0] * 10,
                        [0] * 10]
        self.__ships = []
        self.__hits = []

    def get_element(self, x, y):
        if x > 9 or x < 0 or y > 9 or y < 0:
            raise ValueError("Please enter a valid position!")
        return self.__board[x][y]

    def set_element(self, x, y, value):
        # The board will have 0's for free space, 1's for ship parts and 2's for damaged ship parts
        self.__board[x][y] = value
        if value == 2:
            self.get_ship(x, y).damage_ship([x, y])
        if value == 3:
            self.__hits.append([x, y])

    def get_ship(self, x, y):
        for ship in self.__ships:
            if [x, y] in ship.tiles:
                return ship
        return None

    def set_ship(self, ship, value):
        # the player will be able to set their ships wherever they want on the board
        self.check_ship_placement(ship)
        self.__ships.append(ship)
        for tile in ship.tiles:
            self.set_element(tile[0], tile[1], value)

    def set_found_ship(self, ship, value):
        for tile in ship.tiles:
            self.set_element(tile[0], tile[1], value)

    @staticmethod
    def check_ship_integrity(ship):
        return ship.check_sunk()

    def check_ship_placement(self, ship):
        for pair in ship.tiles:
            if self.get_ship(pair[0], pair[1]) is not None:
                raise LogisticsException("You can't place your ship here!")

    def defeated(self):
        for ship in self.__ships:
            if ship.check_sunk() is False:
                return False
        return True

    def __str__(self):
        board_to_str = "    "
        for letter in "ABCDEFGHIJ":
            board_to_str += letter + " "
        board_to_str += '\n'
        for i in range(10):
            board_to_str += f"{i + 1}  "
            if i != 9:
                board_to_str += ' '
            for value in self.__board[i]:
                if value == 0:
                    board_to_str += '_ '
                elif value == 1:
                    board_to_str += 'O '
                elif value == 2:
                    board_to_str += 'x '
                elif value == 3:
                    board_to_str += '* '
                elif value == 4:
                    board_to_str += '0 '
                elif value == 5:
                    board_to_str += '# '
            board_to_str += '\n'

        return board_to_str

    @property
    def ships(self):
        return self.__ships

    @property
    def hits(self):
        return self.__hits
