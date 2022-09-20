import datetime
import unittest
from src.domain.validators import MovieValidator, ClientValidator, RentalValidator
from src.repository.repo import Repository, RepositoryException
from src.services.services import MovieService, ClientService, RentalService


class MovieServiceTest(unittest.TestCase):
    def setUp(self) -> None:
        self._movie_repo = Repository(MovieValidator())
        self._movie_service = MovieService(self._movie_repo)

    def tearDown(self) -> None:
        pass

    def test_add_movie(self):
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        self.assertEqual(len(self._movie_repo), 1)

    def test_update_movie(self):
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        self.assertEqual(self._movie_repo[1].title, "Title")

        self._movie_service.update_movie(1, "New Title", "Description", "Drama")
        self.assertEqual(self._movie_repo[1].title, "New Title")

    def test_remove_movie(self):
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        self._movie_service.remove_movie(1)
        self.assertEqual(len(self._movie_repo), 0)

    def test_find_movie(self):
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        movie1 = self._movie_service.find_movie(1)
        movie2 = self._movie_service.find_movie("tle")
        movie3 = self._movie_service.find_movie("desc")
        movie4 = self._movie_service.find_movie("This won't be found")

        self.assertEqual(movie1, [self._movie_repo.find_by_id(1)])
        self.assertEqual(movie2, [self._movie_repo.find_by_id(1)])
        self.assertEqual(movie3, [self._movie_repo.find_by_id(1)])
        self.assertEqual(movie4, [])

    def test_get_movie_by_id(self):
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        movie = self._movie_service.get_movie_by_id(1)

        self.assertEqual(movie, self._movie_repo.find_by_id(1))


class ClientServiceTest(unittest.TestCase):
    def setUp(self) -> None:
        self._client_repo = Repository(ClientValidator())
        self._client_service = ClientService(self._client_repo)

    def tearDown(self) -> None:
        pass

    def test_add_client(self):
        self.assertEqual(len(self._client_repo), 0)
        self._client_service.add_client(1, "Name")
        self.assertEqual(len(self._client_repo), 1)

    def test_update_client(self):
        self._client_service.add_client(1, "Name")
        self.assertEqual(self._client_repo[1].name, "Name")
        self._client_service.update_client(1, "New Name")
        self.assertEqual(self._client_repo[1].name, "New Name")

    def test_remove_client(self):
        self._client_service.add_client(1, "Name")
        self._client_service.remove_client(1)
        self.assertEqual(len(self._client_repo), 0)

    def test_find_client(self):
        self._client_service.add_client(1, "Name")
        client1 = self._client_service.find_client(1)
        client2 = self._client_service.find_client("na")
        client3 = self._client_service.find_client("This won't be found")
        self.assertEqual(client1, [self._client_repo.find_by_id(1)])
        self.assertEqual(client2, [self._client_repo.find_by_id(1)])
        self.assertEqual(client3, [])

    def test_get_client_by_id(self):
        self._client_service.add_client(1, "Name")
        client = self._client_service.get_client_by_id(1)
        self.assertEqual(client, self._client_repo[1])


class RentalServiceTest(unittest.TestCase):
    def setUp(self) -> None:
        self._movie_repo = Repository(MovieValidator())
        self._movie_service = MovieService(self._movie_repo)
        self._client_repo = Repository(ClientValidator())
        self._client_service = ClientService(self._client_repo)
        self._rental_repo = Repository(RentalValidator())
        self._rental_service = RentalService(self._rental_repo, self._client_repo, self._movie_repo)

    def tearDown(self) -> None:
        pass

    def test_rent_movie(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        rental_date = "23-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)
        self.assertEqual(len(self._rental_repo), 1)

    def test_return_movie(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")

        rental_date = "23-11-2021"
        return_date = "25-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)
        #self._rental_service.return_movie(1, 1, return_date)

        #self.assertEqual(self._rental_repo[1].return_date, return_date)

    def test_get_rentals_by_client_id(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")

        rental_date = "23-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)

        client_1_rentals = self._rental_service.get_rentals_by_client_id(1)
        self.assertEqual(client_1_rentals, [self._rental_repo[1]])

    """
    def test_get_rentals_by_movie_id(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")

        rental_date = "23-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)

        movie_1_rentals = self._rental_service.get_rentals_by_movie_id(1)
        self.assertEqual(movie_1_rentals, [self._rental_repo[1]])
    """

    def test_get_last_rental_by_movie_id(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")

        rental_date = "23-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)

        last_movie_1_rental = self._rental_service.get_last_client_rental_by_movie_id(1, 1)
        self.assertEqual(last_movie_1_rental, self._rental_repo[1])

    def test_get_days_rented(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")

        rental_date = "23-11-2021"
        return_date = "25-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)
        self._rental_service.return_movie(1, 1, return_date)

        self.assertEqual(self._rental_service.get_days_rented(self._rental_repo[1]), 2)

    def test_get_past_due_days(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")

        rental_date = "23-10-2021"
        return_date = "25-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)
        self._rental_service.return_movie(1, 1, return_date)

        self.assertEqual(self._rental_service.get_past_due_days(self._rental_repo[1]), 3)

    def test_check_rental_possibility(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")

        rental_date = "23-10-2021"
        self._rental_service.rent_movie(1, 1, rental_date)

        with self.assertRaises(RepositoryException) as re:
            self._rental_service.check_rental_possibility(1)
        self.assertEqual(str(re.exception), "You cannot rent any more movies, sorry! Please return overdue movies!")

    def test_check_obj_existence(self):
        with self.assertRaises(RepositoryException) as re:
            self._rental_service.check_obj_existence(1, 1)
        self.assertEqual(str(re.exception), "The account you are trying to access doesn't exist!")

        self._client_service.add_client(1, "Name")

        with self.assertRaises(RepositoryException) as re:
            self._rental_service.check_obj_existence(1, 1)
        self.assertEqual(str(re.exception), "The movie you are trying to access doesn't exist!")

    def test_check_client_rental_status(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        self._movie_service.add_movie(2, "Title", "Description", "Action")

        with self.assertRaises(RepositoryException) as re:
            self._rental_service.check_client_rental_status(1, 1)
        self.assertEqual(str(re.exception), "It appears that Name hasn't made any rentals!")

        rental_date = "23-10-2021"
        return_date = "25-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)
        self._rental_service.return_movie(1, 1, return_date)

        with self.assertRaises(RepositoryException) as re:
            self._rental_service.check_client_rental_status(1, 2)
        self.assertEqual(str(re.exception), "You haven't rented Title yet!")

    def test_most_rented_movies(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        self._movie_service.add_movie(2, "Title", "Description", "Action")

        rental_date = "23-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)
        self._rental_service.rent_movie(2, 1, rental_date)

        return_date1 = "25-11-2021"
        return_date2 = "26-11-2021"
        self._rental_service.return_movie(1, 1, return_date1)
        self._rental_service.return_movie(2, 1, return_date2)

        most_rented = self._rental_service.most_rented_movies()
        self.assertEqual(most_rented, {2: 3, 1: 2})

    def test_most_active_clients(self):
        self._client_service.add_client(1, "Name")
        self._client_service.add_client(2, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        self._movie_service.add_movie(2, "Title", "Description", "Action")

        rental_date = "23-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)
        self._rental_service.rent_movie(2, 2, rental_date)

        return_date1 = "25-11-2021"
        return_date2 = "26-11-2021"
        self._rental_service.return_movie(1, 1, return_date1)
        self._rental_service.return_movie(2, 2, return_date2)

        most_active_clients = self._rental_service.most_active_clients()
        self.assertEqual(most_active_clients, {2: 3, 1: 2})

    def test_late_rentals(self):
        self._client_service.add_client(1, "Name")
        self._movie_service.add_movie(1, "Title", "Description", "Action")
        self._movie_service.add_movie(2, "Title", "Description", "Action")

        rental_date = "23-11-2021"
        self._rental_service.rent_movie(1, 1, rental_date)
        self._rental_service.rent_movie(2, 1, rental_date)

        return_date1 = "25-12-2021"
        return_date2 = "26-12-2021"
        self._rental_service.return_movie(1, 1, return_date1)
        self._rental_service.return_movie(2, 1, return_date2)

        late_rentals = self._rental_service.late_rentals()
        self.assertEqual(late_rentals, {2: 3, 1: 2})
