from datetime import datetime

from src.domaim.domain import Flight, Airport


class FlightServices:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def add_flight(self, id, departure_city, departure_time, arrival_city, arrival_time):
        """
        This function adds a flight
        :param id:
        :param departure_city:
        :param departure_time:
        :param arrival_city:
        :param arrival_time:
        :return:
        """
        departure_time = Flight.convert_to_date(departure_time)
        departure_time = datetime.strptime(departure_time, "%H%M")
        arrival_time = Flight.convert_to_date(arrival_time)
        arrival_time = datetime.strptime(arrival_time, "%H%M")
        new_flight = Flight(id, departure_city, departure_time, arrival_city, arrival_time)
        self.__validator.validate(new_flight)
        self.__repo.save_to_list(new_flight)

    def find_by_id(self, id):
        """
        This function finds a flight by its id
        :param id:
        :return:
        """
        for flight in self.__repo.get_all():
            if flight.id == id:
                return flight
        return None

    def delete_flight(self, id):
        """
        This function deletes an existing flight
        :param id:
        :return:
        """
        self.__repo.remove(id)

    def get_all(self):
        return list(self.__repo.get_all())


class AirportService:
    def __init__(self, repo, flight_repo):
        self.__repo = repo
        self.__flight_repo = flight_repo
        self.__number_of_airports = 1

    def get_airport(self, airport_name):
        """
        This function gets an airport by its name
        :param airport_name:
        :return:
        """
        for airport in self.__repo.get_all():
            if airport.city == airport_name:
                return airport
        return None

    def get_flights_by_airport(self, airport_name):
        """
        This function gets the flights of an airport
        :param airport_name:
        :return:
        """
        for flight in self.__flight_repo.get_all():
            if flight.arrival_city == airport_name or flight.departure_city == airport_name:
                return flight
        return None

    def get_airport_names(self):
        names = []
        for airport in self.__repo.get_all():
            names.append(airport.city)
        return names

    def update_airports(self):
        """
        This function updates the airports and their activity
        :return:
        """
        for flight in self.__flight_repo.get_all():
            if flight.arrival_city not in self.get_airport_names():
                id = self.__number_of_airports
                self.__number_of_airports += 1
                new_airport = Airport(id, flight.arrival_city, 1)
                self.__repo.save_to_list(new_airport)
            else:
                airport = self.get_airport(flight.arrival_city)
                new_airport = Airport(airport.id, airport.city, airport.activity + 1)
                self.__repo.update(airport, new_airport)

            if flight.departure_city not in self.get_airport_names():
                id = self.__number_of_airports
                self.__number_of_airports += 1
                new_airport = Airport(id, flight.departure_city, 1)
                self.__repo.save_to_list(new_airport)
            else:
                airport = self.get_airport(flight.departure_city)
                new_airport = Airport(airport.id, airport.city, airport.activity + 1)
                self.__repo.update(airport, new_airport)

    def get_all(self):
        return self.__repo.get_all()
