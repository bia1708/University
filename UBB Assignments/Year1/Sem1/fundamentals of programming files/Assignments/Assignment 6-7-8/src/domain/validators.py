"""
Validators for Movies, Clients and Rentals
"""
import datetime


class StoreExceptions(Exception):
    pass


class MovieValidator:
    @staticmethod
    def validate(movie):
        if movie.genre not in ["Action", "Comedy", "Drama", "Fantasy", "Horror", "Mystery", "Romance", "Sci-Fi",
                               "Thriller", "Western"]:
            raise StoreExceptions("Please enter a valid genre!")


class ClientValidator:
    @staticmethod
    def validate(client):
        if any(char.isdigit() for char in client.name) or len(client.name) < 2:
            raise StoreExceptions("Please enter a valid name!")


class RentalValidator:
    @staticmethod
    def validate(rental):
        if bool(type(rental.rental_date) is datetime.datetime) is False:
            raise StoreExceptions("Please enter a valid date!")
        elif rental.return_date is not None:
            if bool(type(rental.rental_date) is datetime.datetime) is False:
                raise StoreExceptions("Please enter a valid date!")
