import unittest
from src.repository.repo import Repository, RepositoryException
from src.domain.entities import Movie, Client, Rental
from src.domain.validators import MovieValidator


class RepositoryTest(unittest.TestCase):

    def setUp(self) -> None:
        self._validator = MovieValidator()
        self._repo = Repository(self._validator)

    def tearDown(self) -> None:
        pass

    def test_empty_repo(self):
        self.assertEqual(len(self._repo), 0)

    def test_save_to_list(self):
        movie1 = Movie(1, "Title", "Description", "Action")
        self._repo.save_to_list(movie1)
        self.assertEqual(self._repo[1], movie1)
        self.assertEqual(len(self._repo), 1)

        movie2 = Movie(1, "Title", "Description", "Drama")
        with self.assertRaises(RepositoryException) as re:
            self._repo.save_to_list(movie2)
        self.assertEqual(str(re.exception), "The item with this ID already exists!")

    def test_update(self):
        movie1 = Movie(1, "Title", "Description", "Action")
        self._repo.save_to_list(movie1)
        movie3 = Movie(1, "Title", "Description", "Drama")

        with self.assertRaises(RepositoryException) as re:
            self._repo.update(None, movie3)
        self.assertEqual(str(re.exception), "This item does not exist!")

        self._repo.update(self._repo[1], movie3)
        self.assertEqual(self._repo[1], movie3)

    def test_remove(self):
        movie1 = Movie(1, "Title", "Description", "Action")
        self._repo.save_to_list(movie1)

        self._repo.remove(1)
        self.assertEqual(len(self._repo), 0)


# class ClientRentalsRepositoryTest(unittest.TestCase):
#     def setUp(self) -> None:
#         self._validator = RentalValidator()
#         self._validator1 = MovieValidator()
#         self._validator2 = ClientValidator()
#         self._movie_repo = Repository(self._validator1)
#         self._client_repo = Repository(self._validator2)
#         self._repo = ClientRentalsRepository(self._client_repo, self._movie_repo, self._validator)
#
#     def tearDown(self) -> None:
#         pass
#
#     def test_empty_repo(self):
#         self.assertEqual(len(self._repo), 0)
#
#     def test_save_to_list(self):
#         movie = Movie(1, "Title", "Desc", "Action")
#         client = Client(1, "Name")
#         date1 = datetime.datetime(2021, 11, 15)
#         date2 = datetime.datetime(2021, 12, 15)
#         rental1 = Rental(1, 2, 1, date1, date2)
#         rental2 = Rental(1, 1, 2, date1, date2)
#         rental3 = Rental(1, 1, 1, date1, date2)
#         self._movie_repo.save_to_list(movie)
#         self._client_repo.save_to_list(client)
#
#         with self.assertRaises(RepositoryException) as re:
#             self._repo.save_to_list(1, rental1)
#         self.assertEqual(str(re.exception), "The movie you are trying to rent doesn't exist!")
#
#         with self.assertRaises(RepositoryException) as re:
#             self._repo.save_to_list(2, rental2)
#         self.assertEqual(str(re.exception), "The account you are trying to access doesn't exist!")
#
#         self._repo.save_to_list(1, rental3)
#         self.assertEqual(len(self._repo), 1)
#         self.assertEqual(self._repo[1][0], rental3)
#
#     def test_update_rental(self):
#         movie = Movie(1, "Title", "Desc", "Action")
#         client = Client(1, "Name")
#         date1 = datetime.datetime(2021, 11, 15)
#         date2 = datetime.datetime(2021, 12, 15)
#         date3 = datetime.datetime(2021, 12, 12)
#         rental1 = Rental(1, 1, 1, date1, date2)
#         self._movie_repo.save_to_list(movie)
#         self._client_repo.save_to_list(client)
#         self._repo.save_to_list(1, rental1)
#
#         with self.assertRaises(RepositoryException) as re:
#             self._repo.update_rental(1, 2, date3)
#         self.assertEqual(str(re.exception), "The movie you are trying to return doesn't exist!")
#
#         self._repo.update_rental(1, 1, date3)
#         self.assertEqual(self._repo[1][0].return_date, date3)
#
#     def test_check_client_rental_status(self):
#         client = Client(1, "Name")
#         self._client_repo.save_to_list(client)
#
#         with self.assertRaises(RepositoryException) as re:
#             self._repo.check_client_rental_status(2)
#         self.assertEqual(str(re.exception), "The account you are trying to access doesn't exist!")
#
#         with self.assertRaises(RepositoryException) as re:
#             self._repo.check_client_rental_status(1)
#         self.assertEqual(str(re.exception), "It appears that Name hasn't made any rentals!")
#
#     def test_check_rental_status(self):
#         movie = Movie(1, "Title", "Desc", "Action")
#         client = Client(1, "Name")
#         date1 = datetime.datetime(2021, 10, 15)
#         date2 = datetime.datetime(2021, 11, 15)
#         rental1 = Rental(1, 1, 1, date1, date2)
#         self._movie_repo.save_to_list(movie)
#         self._client_repo.save_to_list(client)
#         self._repo.save_to_list(1, rental1)
#
#         with self.assertRaises(RepositoryException) as re:
#             self._repo.check_rental_possibility(1)
#         self.assertEqual(str(re.exception), "You cannot rent any more movies, sorry! Please return overdue movies!")
