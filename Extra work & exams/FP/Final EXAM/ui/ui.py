from src.domaim.validators import FlightException
from src.repository.repo import RepositoryException


class Console:
    def __init__(self, flight_service, airport_service):
        self.__flight_service = flight_service
        self.__airport_service = airport_service

    @staticmethod
    def print_menu():
        print("Welcome")
        print("Menu:\n"
              "\t1. List Flights\n"
              "\t2. Add flight\n"
              "\t3. Delete flight\n"
              "\t4. List airports\n")

    def ui_list_flights(self):
        for flight in self.__flight_service.get_all():
            print(flight)

    def ui_add_flight(self):
        try:
            id = input("ID: ")
            departure_time = input("Departure time: ")
            departure_city = input("Departure city: ")
            arrival_time = input("Arrival time: ")
            arrival_city = input("Arrival city: ")
            self.__flight_service.add_flight(id, departure_city, departure_time, arrival_city, arrival_time)
        except RepositoryException as re:
            print(re)
        except FlightException as fe:
            print(fe)

    def ui_delete_flight(self):
        try:
            id = input("ID: ")
            self.__flight_service.delete_flight(id)
        except RepositoryException as re:
            print(re)

    def ui_list_airports(self):
        for airport in self.__airport_service.get_all():
            print(airport)

    def run(self):
        commands = {
            "1": self.ui_list_flights,
            "2": self.ui_add_flight,
            "3": self.ui_delete_flight,
            "4": self.ui_list_airports
        }

        while True:
            self.print_menu()
            self.__airport_service.update_airports()
            cmd = input("Option: ")
            if cmd == "x":
                break
            else:
                try:
                    commands[cmd]()
                except KeyError as ke:
                    print(str(ke) + "is not a valid command! Please try again!")