"""
Implemented a new iterable data structure, along with a sorting function() and a filter function for the sort
"""


class DataStructure:
    def __init__(self, my_list=None):
        if my_list is None:
            my_list = {}
        self.__data_structure = my_list

    def __len__(self):
        return len(self.__data_structure)

    def __setitem__(self, key, value):
        self.__data_structure[key] = value

    def __getitem__(self, item):
        return self.__data_structure[item]

    def __delitem__(self, key):
        del self.__data_structure[key]

    def __iter__(self):
        self.key = 0
        return self

    def __next__(self):
        self.key += 1
        if self.key >= len(self.__data_structure):
            raise StopIteration
        return self.__data_structure[self.key]

    def append(self, item):
        self.__data_structure.append(item)

    def remove(self, item):
        self.__data_structure.pop(item)

    def keys(self):
        return list(self.__data_structure.keys())

    def values(self):
        return list(self.__data_structure.values())

    def items(self):
        return list(self.__data_structure.items())

    def clear(self):
        self.__data_structure.clear()


# For this assignment I implemented gnome sort :)
def sort(array):

    def compare(elem_1, elem_2):
        return elem_1 >= elem_2

    pos = 0
    while pos < len(array):
        if pos == 0 or compare(array[pos], array[pos - 1]):
            pos += 1
        else:
            array[pos], array[pos - 1] = array[pos - 1], array[pos]
            pos -= 1


def filter_function(old_list, acceptance_function):
    new_list = []
    for element in old_list:
        if acceptance_function(element) is True:
            new_list.append(element)
    return new_list
