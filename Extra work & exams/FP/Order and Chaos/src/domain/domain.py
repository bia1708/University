from texttable import Texttable


class Board:
    def __init__(self):
        self.__board = {0: [" "] * 8, 1: [" "] * 8, 2: [" "] * 8, 3: [" "] * 8, 4: [" "] * 8, 5: [" "] * 8}
        self.__x_symbols = []
        self.__o_symbols = []

    def get_board(self):
        return self.__board

    def set_x_symbols(self, value):
        self.__board[value[0]][value[1]] = "x"
        self.__x_symbols.append(value)

    def get_x_symbols(self):
        return self.__x_symbols

    def get_o_symbols(self):
        return self.__o_symbols

    def set_o_symbols(self, value):
        self.__board[value[0]][value[1]] = "o"
        self.__o_symbols.append(value)

    def __getitem__(self, item):
        return self.__board[item]

    def __setitem__(self, key, value):
        self.__board[key] = value

    def __str__(self, mode=None):
        string = Texttable()
        for i in range(6):
            string.add_row(self.__board[i])
        return string.draw()
