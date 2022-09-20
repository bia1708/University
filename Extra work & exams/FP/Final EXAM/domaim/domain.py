from datetime import datetime

class Flight:
    def __init__(self, id, departure_city, departure_time, arrival_city, arrival_time):
        self.__id = id
        self.__departure_city = departure_city
        self.__departure_time = departure_time
        self.__arrival_city = arrival_city
        self.__arrival_time = arrival_time

    @property
    def id(self):
        return self.__id

    @property
    def departure_city(self):
        return self.__departure_city

    @departure_city.setter
    def departure_city(self, value):
        self.__departure_city = value

    @property
    def departure_time(self):
        return self.__departure_time

    @departure_time.setter
    def departure_time(self, value):
        self.__departure_time = value

    @property
    def arrival_city(self):
        return self.__arrival_city

    @arrival_city.setter
    def arrival_city(self, value):
        self.__arrival_city = value

    @property
    def arrival_time(self):
        return self.__arrival_time

    @arrival_time.setter
    def arrival_time(self, value):
        self.__arrival_time = value

    def __str__(self):
        string = ""
        string += f"Id: {self.__id} || Departure time: {self.__departure_time} || Departure City: {self.__departure_city}" \
                  f"|| Arrival Time: {self.__arrival_time} || Arrival City: {self.__arrival_city}"
        return string

    @staticmethod
    def flight_to_line(flight):
        departure_time = datetime.strftime(flight.departure_time, "%H:%M")
        arrival_time = datetime.strftime(flight.arrival_time, "%H:%M")
        return f"{flight.__id},{flight.__departure_city},{departure_time},{flight.__arrival_city}" \
               f",{arrival_time}"

    @staticmethod
    def line_to_flight(line):
        text = line.split(",")
        departure_time = Flight.convert_to_date(text[2])
        departure_time = datetime.strptime(departure_time, "%H%M")
        arrival_time = Flight.convert_to_date(text[4])
        arrival_time = datetime.strptime(arrival_time, "%H%M")

        return Flight(text[0], text[1], departure_time, text[3], arrival_time)

    @staticmethod
    def convert_to_date(date):
        date = date.split(":")
        new_date = date[0] + date[1]
        return new_date


class Airport:
    def __init__(self, id, city, activity):
        self.__id = id
        self.__city = city
        self.__activity = activity

    @property
    def id(self):
        return self.__id

    @property
    def city(self):
        return self.__city

    @city.setter
    def city(self, value):
        self.__city = value

    @property
    def activity(self):
        return self.__activity

    @activity.setter
    def activity(self, value):
        self.__activity = value

    def __str__(self):
        string = f"ID: {self.__id} || City: {self.__city} || Activity: {self.__activity}"
        return string
