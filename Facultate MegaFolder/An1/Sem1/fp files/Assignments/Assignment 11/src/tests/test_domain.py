from src.domain.domain import Ship
import unittest


class TestDomain(unittest.TestCase):
    def setUp(self) -> None:
        self.__ship = Ship([0, 0], [0, 4])

    def test_length(self):
        self.assertEqual(len(self.__ship), 5)

    def test_tiles(self):
        self.assertEqual(self.__ship.tiles, [[0, 0], [0, 1], [0, 2], [0, 3], [0, 4]])

    def test_starting_pos(self):
        self.assertEqual(self.__ship.starting_pos, [0, 0])

    def test_damage_ship(self):
        self.__ship.damage_ship([0, 0])
        self.assertEqual(self.__ship.tiles, [[0], [0, 1], [0, 2], [0, 3], [0, 4]])

    def test_check_sunk(self):
        self.assertEqual(self.__ship.check_sunk(), False)
        self.__ship.damage_ship([0, 0])
        self.__ship.damage_ship([0, 1])
        self.__ship.damage_ship([0, 2])
        self.__ship.damage_ship([0, 3])
        self.__ship.damage_ship([0, 4])
        self.assertEqual(self.__ship.check_sunk(), True)
