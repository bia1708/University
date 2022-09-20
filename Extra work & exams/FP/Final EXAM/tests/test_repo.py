import unittest

from src.domaim.domain import Airport
from src.repository.repo import Repository


class TestRepo(unittest.TestCase):
    def setUp(self) -> None:
        self.__repo = Repository()

    def test_add_elem(self):
        self.assertEqual(len(self.__repo), 0)
        elem = Airport(1, "Paris", 1)
        self.__repo.save_to_list(elem)
        self.assertEqual(len(self.__repo), 1)

    def test_remove_from_repo(self):
        elem = Airport(1, "Paris", 1)
        self.__repo.save_to_list(elem)
        self.assertEqual(len(self.__repo), 1)
        self.__repo.remove(elem.id)
        self.assertEqual(len(self.__repo), 0)

    def test_update_elem(self):
        elem = Airport(1, "Paris", 1)
        self.__repo.save_to_list(elem)
        new_elem = Airport(1, "Paris", 2)

        self.__repo.update(elem, new_elem)
        self.assertEqual(self.__repo[1].activity, 2)