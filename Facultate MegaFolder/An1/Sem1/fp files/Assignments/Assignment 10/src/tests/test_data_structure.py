from src.misc.data_structure import DataStructure, sort, filter_function
import unittest

class DataStructureTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__data1 = DataStructure([1, 3, 5, 6])
        self.__data2 = DataStructure()

    def test_len(self):
        self.assertEqual(len(self.__data1), 4)

    def test_set_item(self):
        self.__data2[4] = 5
        self.assertEqual(len(self.__data2), 1)
        self.assertEqual(self.__data2[4], 5)

    def test_get_item(self):
        item = self.__data1[0]
        self.assertEqual(item, 1)

    def test_remove_item(self):
        self.__data1.remove(1)
        self.assertEqual(self.__data1[1], 5)
        self.assertEqual(len(self.__data1), 3)

    def test_append(self):
        self.__data1.append(9)
        self.assertEqual(self.__data1[4], 9)

    def test_next(self):
        self.__data2[0] = 1
        self.__data2[1] = 2
        iterator = 0
        for iterator in self.__data2:
            iterator += 1
        self.assertEqual(iterator, 3)

    def test_del(self):
        self.__data2[0] = 1
        self.__data2.__delitem__(0)
        self.assertEqual(len(self.__data2), 0)

    def test_keys(self):
        self.__data2[0] = 1
        self.__data2[1] = 2
        key_list = self.__data2.keys()
        self.assertEqual(key_list, [0, 1])

    def test_values(self):
        self.__data2[0] = 1
        self.__data2[1] = 2
        value_list = self.__data2.values()
        self.assertEqual(value_list, [1, 2])

    def test_items(self):
        self.__data2[0] = 1
        self.__data2[1] = 2
        items_list = self.__data2.items()
        self.assertEqual(items_list, [(0, 1), (1, 2)])

    def test_clear(self):
        self.__data2[0] = 1
        self.__data2[1] = 2
        self.__data2.clear()
        self.assertEqual(len(self.__data2), 0)


class SortTest(unittest.TestCase):
    def setUp(self) -> None:
        self.array = [1, 5, 8, 4]

    def test_sort(self):
        sort(self.array)
        self.assertEqual(self.array, [1, 4, 5, 8])


class FilterTest(unittest.TestCase):
    def setUp(self) -> None:
        self.array = [1, 2, 6, 7, 4]

    def test_filter(self):
        filtered_list = filter_function(self.array, lambda x: x >= 4)
        self.assertEqual(filtered_list, [6, 7, 4])