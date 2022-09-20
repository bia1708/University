from random import randint

from src.domain.entities import Taxi, Ride


class TaxiService:
    def __init__(self, repo):
        self.__repo = repo

    @staticmethod
    def generate_random_coord():
        x = randint(0, 100)
        y = randint(0, 100)
        return x, y

    @staticmethod
    def calculate_distance(pair1, pair2):
        distance = abs(pair2[0] - pair1[0]) + abs(pair2[1] - pair1[1])
        return distance

    def check_coords_validity(self, coords):
        for taxi in self.__repo.get_all():
            if self.calculate_distance(coords, [taxi.x_position, taxi.y_position]) < 5:
                return False
        return True

    def add_taxis(self, number_of_taxis):
        coords = self.generate_random_coord()
        new_taxi = Taxi(1, coords[0], coords[1])
        self.__repo.save_to_list(new_taxi)

        for i in range(number_of_taxis):
            coords = self.generate_random_coord()
            while self.check_coords_validity(coords) is False:
                coords = self.generate_random_coord()

            new_taxi = Taxi(i + 1, coords[0], coords[1])
            self.__repo.save_to_list(new_taxi)

    def get_all_taxis(self):
        return self.__repo.get_all()


class RideService:
    def __init__(self, repo, taxi_repo):
        self.__repo = repo
        self.__taxi_repo = taxi_repo
        self.__number_of_rides = 0

    @staticmethod
    def calculate_distance(pair1, pair2):
        distance = abs(pair2[0] - pair1[0]) + abs(pair2[1] - pair1[1])
        return distance

    def find_taxi(self, start_point):
        minimum_distance = 200
        good_taxi_id = 0
        for taxi in self.__taxi_repo.get_all():
            distance = self.calculate_distance(start_point, [taxi.x_position, taxi.y_position])
            if distance < minimum_distance:
                minimum_distance = distance
                good_taxi_id = taxi.id

        return self.__taxi_repo[good_taxi_id]

    def add_ride(self, start_point, end_point):
        """
        This function adds a new ride and updates the taxi accordingly
        :param start_point: a list with the coords for the starting point
        :param end_point: a list with the coords for the end point
        :return:
        """
        taxi = self.find_taxi(start_point)
        self.__number_of_rides += 1
        new_ride = Ride(self.__number_of_rides, taxi.id, start_point, end_point)
        self.__repo.save_to_list(new_ride)
        fare = taxi.total_fare + self.calculate_distance(start_point, end_point)
        updated_taxi = Taxi(taxi.id, end_point[0], end_point[1], fare)
        self.__taxi_repo.update(taxi, updated_taxi)