import unittest
from src.domain.board import Board, LogisticsException
from src.domain.domain import Ship


class TestBoard(unittest.TestCase):
    def setUp(self) -> None:
        self.__board = Board()

    def test_set_element_get_element(self):
        self.__board.set_element(0, 0, 4)
        self.assertEqual(self.__board.get_element(0, 0), 4)

        with self.assertRaises(ValueError) as ve:
            self.__board.get_element(30, -50)
        self.assertEqual(str(ve.exception), "Please enter a valid position!")

    def test_set_ship_get_ship(self):
        ship = Ship([0, 0], [0, 5])
        self.__board.set_ship(ship, 1)
        self.assertEqual(self.__board.get_ship(0, 5), ship)
        self.assertEqual(self.__board.defeated(), False)

        self.__board.set_found_ship(ship, 2)
        self.assertEqual(self.__board.check_ship_integrity(ship), True)
        self.assertEqual(self.__board.defeated(), True)

    def test_check_ship_placement(self):
        ship = Ship([0, 0], [0, 5])
        self.__board.set_ship(ship, 1)
        ship2 = Ship([0, 0], [0, 4])

        with self.assertRaises(LogisticsException) as le:
            self.__board.check_ship_placement(ship2)
        self.assertEqual(str(le.exception), "You can't place your ship here!")

    def test_get_ships(self):
        ship1 = Ship([0, 0], [0, 5])
        ship2 = Ship([1, 0], [1, 4])
        self.__board.set_ship(ship1, 1)
        self.__board.set_ship(ship2, 1)
        self.assertEqual(self.__board.ships, [ship1, ship2])

    def test_get_hits(self):
        self.__board.set_element(0, 0, 3)
        self.assertEqual(self.__board.hits, [[0, 0]])

    def test_str(self):
        self.__board.set_element(0, 0, 1)
        ship = Ship([0, 1], [0, 1])
        self.__board.set_ship(ship, 2)
        self.__board.set_element(0, 2, 3)
        self.__board.set_element(0, 3, 4)
        self.__board.set_element(0, 4, 5)

        self.assertEqual(str(self.__board), "    A B C D E F G H I J \n1   O x * 0 # _ _ _ _ _ \n2   _ _ _ _ _ _ _ _ _ _ \n"
                                            "3   _ _ _ _ _ _ _ _ _ _ \n4   _ _ _ _ _ _ _ _ _ _ \n5   _ _ _ _ _ _ _ _ _ _ \n"
                                            "6   _ _ _ _ _ _ _ _ _ _ \n7   _ _ _ _ _ _ _ _ _ _ \n8   _ _ _ _ _ _ _ _ _ _ \n"
                                            "9   _ _ _ _ _ _ _ _ _ _ \n10  _ _ _ _ _ _ _ _ _ _ \n")

