class Taxi:
    def __init__(self, id, x_position, y_position, total_fare=0):
        self.__id = id
        self.__x_pos = x_position
        self.__y_pos = y_position
        self.__total_fare = total_fare

    @property
    def id(self):
        return self.__id

    @property
    def x_position(self):
        return self.__x_pos

    @x_position.setter
    def x_position(self, value):
        self.__x_pos = value

    @property
    def y_position(self):
        return self.__y_pos

    @y_position.setter
    def y_position(self, value):
        self.__y_pos = value

    @property
    def total_fare(self):
        return self.__total_fare

    @total_fare.setter
    def total_fare(self, value):
        self.__total_fare = value

    def __str__(self):
        taxi_to_str = ""
        left_justified = str(self.__id)
        right_justified = f"({self.__x_pos}, {self.__y_pos})  " + str(self.__total_fare)
        right_justified = right_justified.rjust(30)
        taxi_to_str = left_justified + right_justified
        return taxi_to_str


class Ride:
    def __init__(self, id, taxi_id, start_point, end_point):
        self.__id = id
        self.__taxi_id = taxi_id
        self.__start_point = start_point
        self.__end_point = end_point

    @property
    def id(self):
        return self.__id

    @property
    def taxi_id(self):
        return self.__taxi_id

    @taxi_id.setter
    def taxi_id(self, value):
        self.__taxi_id = value

    @property
    def start_point(self):
        return self.__start_point

    @start_point.setter
    def start_point(self, value):
        self.__start_point = value

    @property
    def end_point(self):
        return self.__end_point

    @end_point.setter
    def end_point(self, value):
        self.__end_point = value