class GameException(Exception):
    pass


class PositionValidator:
    @staticmethod
    def validate(x, y):
        if x > 9 or x < 0 or y > 9 or y < 0:
            raise GameException("Please enter a valid position!")


class ShipValidator:
    @staticmethod
    def validate(start_pos, end_pos, length):
        if start_pos[0] == end_pos[0]:  # horizontal ship
            if end_pos[1] - start_pos[1] + 1 != length:
                raise GameException("Please enter a valid ship!")
        elif start_pos[1] == end_pos[1]:  # vertical ship
            if end_pos[0] - start_pos[0] + 1 != length:
                raise GameException("Please enter a valid ship!")
        else:
            raise GameException("Please enter a valid ship!")
