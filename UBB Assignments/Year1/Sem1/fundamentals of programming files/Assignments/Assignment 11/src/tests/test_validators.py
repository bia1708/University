from src.domain.validators import ShipValidator, PositionValidator, GameException
import unittest


class TestValidators(unittest.TestCase):
    def setUp(self) -> None:
        self.__position_validator = PositionValidator()
        self.__ship_validator = ShipValidator()

    def test_validate_position(self):
        with self.assertRaises(GameException) as ge:
            self.__position_validator.validate(15, 14)
        self.assertEqual(str(ge.exception), "Please enter a valid position!")

    def test_validate_ship(self):
        with self.assertRaises(GameException) as ge:
            self.__ship_validator.validate([0, 0], [0, 2], 4)
        self.assertEqual(str(ge.exception), "Please enter a valid ship!")

        with self.assertRaises(GameException) as ge:
            self.__ship_validator.validate([0, 0], [2, 0], 4)
        self.assertEqual(str(ge.exception), "Please enter a valid ship!")

        with self.assertRaises(GameException) as ge:
            self.__ship_validator.validate([5, 0], [0, 2], 4)
        self.assertEqual(str(ge.exception), "Please enter a valid ship!")
