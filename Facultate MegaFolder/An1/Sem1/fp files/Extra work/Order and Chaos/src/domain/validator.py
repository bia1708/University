class ValueException(Exception):
    pass


class Validator:
    @staticmethod
    def validate(x_pos, y_pos, symbol):
        if x_pos < 0 or x_pos > 5 or y_pos < 0 or y_pos > 5:
            raise ValueException("Please enter a valid position on the board!")
        if symbol not in ["x", "o"]:
            raise ValueException("Please enter a valid symbol!")
