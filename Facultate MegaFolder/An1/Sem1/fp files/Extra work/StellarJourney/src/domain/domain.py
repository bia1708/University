from texttable import Texttable


class Board:
    def __init__(self):
        self.__board = {0: [" "] * 8, 1: [" "] * 8, 2: [" "] * 8, 3: [" "] * 8, 4: [" "] * 8, 5: [" "] * 8, 6: [" "] * 8,
                        7: [" "] * 8}
        self.__stars = []
        self.__b_ships = []
        self.__my_ship = []

    def get_board(self):
        return self.__board

    def new_star(self, value):
        self.__stars.append(value)

    def get_stars(self):
        return self.__stars

    def get_enemy_ships(self):
        return self.__b_ships

    def delete_enemy_ships(self):
        self.__b_ships.clear()

    def set_enemy_ship(self, value):
        self.__b_ships.append(value)

    def get_player_ship(self):
        return self.__my_ship[0][0], self.__my_ship[0][1]

    def set_player_ship(self, value):
        self.__my_ship.clear()
        self.__my_ship.append(value)

    def __getitem__(self, item):
        return self.__board[item]

    def __setitem__(self, key, value):
        self.__board[key] = value

    def __str__(self, mode=None):
        string = Texttable()
        letters = ["A", "B", "C", "D", "E", "F", "G", "H"]
        string.add_row([" ", "1", "2", "3", "4", "5", "6", "7", "8"])
        for i in range(8):
            string.add_row([letters[i]] + self.__board[i])
        return string.draw()
