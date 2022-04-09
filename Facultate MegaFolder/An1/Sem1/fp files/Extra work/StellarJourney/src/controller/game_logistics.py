from random import randint


class GameException(Exception):
    pass


class EndingException(Exception):
    pass


class GameLogistics:
    def __init__(self, game_board, player_board):
        self.__game_board = game_board
        self.__player_board = player_board

    def check_star_placement(self, x, y):
        if len(self.__game_board.get_stars()) > 0:
            for star in self.__game_board.get_stars():
                if star[0] == x and star[1] == y:
                    return False
                elif abs(star[0] - x) == 1 and abs(star[1] - y) <= 1:
                    return False
                elif abs(star[1] - y) == 1 and abs(star[0] - x) <= 1:
                    return False
        return True

    def place_stars(self):
        for i in range(10):
            choice = True
            while choice:
                x = randint(0, 7)
                y = randint(0, 7)
                if self.check_star_placement(x, y) is True:
                    self.__game_board.new_star([x, y])
                    self.__player_board.new_star([x, y])
                    self.__player_board[x][y] = "*"
                    self.__game_board[x][y] = "*"
                    choice = False

    def place_player_ship(self):
        # this is the situation for the beginning of the game, when the ship is placed randomly
        choice = True
        while choice:
            x = randint(0, 7)
            y = randint(0, 7)
            if self.__game_board[x][y] == " ":
                self.__game_board.set_player_ship([x, y])
                self.__player_board.set_player_ship([x, y])
                self.__game_board[x][y] = "E"
                self.__player_board[x][y] = "E"
                choice = False

    def update_player_board(self):
        x, y = self.__player_board.get_player_ship()
        for ship in self.__game_board.get_enemy_ships():
            if (abs(ship[0] - x) == 1 and abs(ship[1] - y) <= 1) or (abs(ship[1] - y) == 1 and abs(ship[0] - x) <= 1):
                self.__player_board[ship[0]][ship[1]] = "B"

    def place_enemy_ships(self, number):
        for i in range(number):
            choice = True
            while choice:
                x = randint(0, 7)
                y = randint(0, 7)
                if self.__game_board[x][y] == " ":
                    self.__game_board.set_enemy_ship([x, y])
                    self.__game_board[x][y] = "B"
                    choice = False

    def move_player(self, x, y):
        # this is the situation when the player moves his ship
        old_x = self.__game_board.get_player_ship()[0]
        old_y = self.__game_board.get_player_ship()[1]
        if x == old_x or y == old_y or \
                abs(x - self.__game_board.get_player_ship()[0]) == abs(y - self.__game_board.get_player_ship()[1]):
            if self.__game_board[x][y] == "*":
                raise GameException("You can't place your ship here!")
            elif self.__game_board[x][y] == "B":
                raise EndingException("GAME OVER!!! YOU LOST!")
            else:
                self.__game_board.set_player_ship([x, y])
                self.__player_board.set_player_ship([x, y])
                self.__player_board[x][y] = "E"
                self.__game_board[x][y] = "E"
                self.__player_board[old_x][old_y] = " "
                self.__game_board[old_x][old_y] = " "
        else:
            raise GameException("You can't place your ship here!")

    def fire_player(self, x, y):
        if self.__game_board[x][y] == "B":
            number_of_enemy_ships = len(self.__game_board.get_enemy_ships())
            self.__player_board[x][y] = " "
            for ship in self.__game_board.get_enemy_ships():
                self.__game_board[ship[0]][ship[1]] = " "
            self.__game_board.delete_enemy_ships()
            self.place_enemy_ships(number_of_enemy_ships - 1)
        else:
            raise GameException("You can't fire here!")

    def get_game_board(self):
        return self.__game_board

    def get_player_board(self):
        return self.__player_board

    def game_status(self):
        if len(self.__game_board.get_enemy_ships()) == 0:
            return 1
        else:
            return 0
