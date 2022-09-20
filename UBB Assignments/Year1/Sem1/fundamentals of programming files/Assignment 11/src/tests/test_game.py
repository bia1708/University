import unittest

from src.game_logistics.ai import Computer
from src.game_logistics.game_logistics import Game, GameStatus


class TestGame(unittest.TestCase):
    def setUp(self) -> None:
        self.__game = Game(Computer("smart"))

    def test_game_status(self):
        self.assertEqual(self.__game.game_status(), 1)

        self.__game.set_ship([0, 0], [0, 1], 2)

        self.assertEqual(self.__game.game_status(), 3)

        self.__game.computer_ships()
        self.assertEqual(self.__game.game_status(), 0)

    def test_get_rounds(self):
        self.assertEqual(self.__game.rounds, 1)
        self.__game.increase_round()
        self.assertEqual(self.__game.rounds, 2)

    def test_get_board(self):
        self.__game.set_ship([0, 0], [0, 1], 2)
        self.assertEqual(self.__game.get_board("player").get_element(0, 0), 1)

        self.assertEqual(self.__game.get_board("computer").get_element(0, 0), 0)

        self.__game.move_player(0, 0)
        self.assertEqual(self.__game.get_board("strategy").get_element(0, 0), 4)

