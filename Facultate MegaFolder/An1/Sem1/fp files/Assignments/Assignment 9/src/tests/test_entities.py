from src.domain.entities import Movie, Client, Rental
from src.domain.validators import MovieValidator, ClientValidator, RentalValidator, StoreExceptions
import unittest


class EntitiesTest(unittest.TestCase):
    def setUp(self) -> None:
        self._movie_validator = MovieValidator()
        self._client_validator = ClientValidator()
        self._rental_validator = RentalValidator()

    def tearDown(self) -> None:
        pass

    def test_client(self):
        client = Client(1, "George Michael")
        self._client_validator.validate(client)
        self.assertEqual(client.id, 1)
        self.assertEqual(client.name, "George Michael")

        bad_client = Client(2, "")
        with self.assertRaises(StoreExceptions) as se:
            self._client_validator.validate(bad_client)
        self.assertEqual(str(se.exception), "Please enter a valid name!")

    def test_movie(self):
        movie = Movie(1, "A movie", "This description looks kinda bad here but it's all I could do.", "Boring")
        self.assertEqual(movie.id, 1)
        self.assertEqual(movie.title, "A movie")

        bad_movie = Movie(2, "A movie", "A description", "Bad genre")
        with self.assertRaises(StoreExceptions) as se:
            self._movie_validator.validate(bad_movie)
        self.assertEqual(str(se.exception), "Please enter a valid genre!")

    def test_rental(self):
        rental = Rental(1, 2, 3, "1-1-2021", "31-1-2021")
        self.assertEqual(rental.return_date, None)
        self.assertEqual(rental.id, 1)

        bad_rental_1 = Rental(2, 3, 1, "31-13-3031", "12-12-2021")
        with self.assertRaises(StoreExceptions) as se:
            self._rental_validator.validate(bad_rental_1)
        self.assertEqual(str(se.exception), "Please enter a valid date!")

        bad_rental_2 = Rental(3, 4, 5, "05-03-2021", "23-02-2020", "33-03-2020")
        with self.assertRaises(StoreExceptions) as se:
            self._rental_validator.validate(bad_rental_2)
        self.assertEqual(str(se.exception), "Please enter a valid date!")
