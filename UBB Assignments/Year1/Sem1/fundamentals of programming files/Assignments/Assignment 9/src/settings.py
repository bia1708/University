from src.domain.entities import Movie, Client, Rental
from src.repository.repo import Repository, TextFileRepository, BinFileRepository
from src.domain.validators import MovieValidator, ClientValidator, RentalValidator


class Properties:
    def __init__(self, file_type):
        self.__file_type = file_type

    @staticmethod
    def validator_settings():
        movie_validator = MovieValidator()
        client_validator = ClientValidator()
        rental_validator = RentalValidator()
        return movie_validator, client_validator, rental_validator

    def repository_settings(self):
        if self.__file_type == 'bin':
            movie_repo = BinFileRepository("movies.bin", Movie.line_to_movie, Movie.movie_to_line)
            client_repo = BinFileRepository("clients.bin", Client.line_to_client, Client.client_to_line)
            rental_repo = BinFileRepository("rentals.bin", Rental.line_to_rental, Rental.rental_to_line)
        elif self.__file_type == 'txt':
            movie_repo = TextFileRepository("movies.txt", Movie.line_to_movie, Movie.movie_to_line)
            client_repo = TextFileRepository("clients.txt", Client.line_to_client, Client.client_to_line)
            rental_repo = TextFileRepository("rentals.txt", Rental.line_to_rental, Rental.rental_to_line)
        else:
            movie_repo = Repository()
            client_repo = Repository()
            rental_repo = Repository()

        return movie_repo, client_repo, rental_repo
