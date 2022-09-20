from copy import copy


class GameException(Exception):
    pass


class GameLogistics:
    def __init__(self, board, validator, ai):
        self.__board = board
        self.__validator = validator
        self.__ai = ai

    def place_symbol(self, x_pos, y_pos, symbol):
        self.__validator.validate(x_pos, y_pos, symbol)
        choice = True
        if self.check_placement(x_pos, y_pos) is True:
            if symbol == "x":
                self.__board.set_x_symbols([x_pos, y_pos])
            else:
                self.__board.set_o_symbols([x_pos, y_pos])

    def computer_move(self):
        computer_pos, computer_symbol = self.__ai.move()
        self.place_symbol(computer_pos[0], computer_pos[1], computer_symbol)

    def check_placement(self, x_pos, y_pos):
        if [x_pos, y_pos] in self.__board.get_o_symbols():
            raise GameException("You can't place a symbol here!")

        if [x_pos, y_pos] in self.__board.get_x_symbols():
            raise GameException("You can't place a symbol here!")

        return True

    def check_won(self):
        for i in range(0, 6):
            for j in range(0, 6):
                good_symbol = True
                if self.__board[i][j] != " ":
                    # check for horizontal
                    for q in range(5):
                        if j + q < 6 and self.__board[i][j + q] != self.__board[i][j]:
                            good_symbol = False
                    if good_symbol is True:
                        return True

                    # check for vertical
                    for q in range(5):
                        if i + q < 6 and self.__board[i + q][j] != self.__board[i][j]:
                            good_symbol = False
                    if good_symbol is True:
                        return True

                    # check first diagonal
                    for q in range(5):
                        if i + q < 6 and j + q < 6 and self.__board[i + q][j + q] != self.__board[i][j]:
                            good_symbol = False
                    if good_symbol is True:
                        return True

                    # check secondary diagonal
                    for q in range(5):
                        if i + q < 6 and j - q >= 0 and self.__board[i + q][j - q] != self.__board[i][j]:
                            good_symbol = False
                    if good_symbol is True:
                        return True
        return False

    def check_game_status(self):
        if self.check_won() is True:
            return "over"
        if len(self.__board.get_o_symbols()) + len(self.__board.get_x_symbols()) == 36:
            return "computer_won"
        return "ongoing"

    def get_board(self):
        return self.__board


class Computer:
    def __init__(self, board):
        self.__board = board

    def get_most_used_symbol(self):
        if len(self.__board.get_x_symbols()) > len(self.__board.get_o_symbols()):
            return "x"
        else:
            return "o"

    def check_vicinity(self, x_pos, y_pos, symbol):
        number_of_symbols = 0

        for q in range(0, 2):
            # horizontal search
            if x_pos + q < 6 and self.__board[x_pos + q][y_pos] == symbol:
                number_of_symbols += 1

            if x_pos - q >= 0 and self.__board[x_pos - q][y_pos] == symbol:
                number_of_symbols += 1

            # vertical search
            if y_pos + q < 6 and self.__board[x_pos][y_pos + q] == symbol:
                number_of_symbols += 1

            if y_pos - q >= 0 and self.__board[x_pos][y_pos - q] == symbol:
                number_of_symbols += 1

            # first diagonal search
            if x_pos + q < 6 and y_pos + q < 6 and self.__board[x_pos + q][y_pos + q] == symbol:
                number_of_symbols += 1

            if x_pos - q >= 0 and y_pos - q >= 0 and self.__board[x_pos - q][y_pos - q] == symbol:
                number_of_symbols += 1

            # secondary diagonal search
            if x_pos + q < 6 and y_pos - q >= 0 and self.__board[x_pos + q][y_pos - q] == symbol:
                number_of_symbols += 1

            if x_pos - q >= 0 and y_pos + q < 6 and self.__board[x_pos - q][y_pos + q] == symbol:
                number_of_symbols += 1

        return number_of_symbols

    def move(self):
        computer_symbol = self.get_most_used_symbol()
        best_position = []
        max_vicinity = 0
        for i in range(6):
            for j in range(6):
                if self.__board[i][j] == " ":
                    number_of_symbols = self.check_vicinity(i, j, computer_symbol)
                    if number_of_symbols > max_vicinity:
                        max_vicinity = copy(number_of_symbols)
                        best_position = [i, j]
        return best_position, computer_symbol
