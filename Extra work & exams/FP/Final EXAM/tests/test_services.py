import unittest

from src.domaim.domain import Airport, Flight
from src.domaim.validators import FlightValidator, FlightException
from src.repository.repo import Repository
from src.services.services import AirportService, FlightServices


class TestAirportServices(unittest.TestCase):
    def setUp(self) -> None:
        self.__repo = Repository()
        self.__flight_repo = Repository()
        self.__service = AirportService(self.__repo, self.__flight_repo)

    def test_update_airports(self):
        self.__flight_repo.save_to_list(Flight(1, "Paris", "12:00", "Rome", "13:00"))
        self.__service.update_airports()
        self.assertEqual(len(self.__repo), 2)

    def test_get_airport(self):
        self.__flight_repo.save_to_list(Flight(1, "Paris", "12:00", "Rome", "13:00"))
        self.__service.update_airports()
        airport = self.__service.get_airport("Paris")
        self.assertEqual(airport, self.__repo[2])


class TestFlightServices(unittest.TestCase):
    def setUp(self) -> None:
        self.__repo = Repository()
        self.__validator = FlightValidator()
        self.__service = FlightServices(self.__repo, self.__validator)

    def test_add_flight(self):
        self.__service.add_flight(1, "Madrid", "12:30", "Bucharest", "13:30")
        self.assertEqual(len(self.__repo), 1)

        with self.assertRaises(FlightException) as fe:
            self.__service.add_flight(2, "fdu", "12:30", "sdfjh", "12:40")
        self.assertEqual(str(fe.exception),"Invalid flight times!")

    def test_remove_flight(self):
        self.__service.add_flight(1, "Madrid", "12:30", "Bucharest", "13:30")
        self.__service.delete_flight(1)
        self.assertEqual(len(self.__repo), 0)

    def test_find_by_id(self):
        self.__service.add_flight(1, "Madrid", "12:30", "Bucharest", "13:30")
        flight = self.__service.find_by_id(1)
        self.assertEqual(flight, self.__repo[1])
