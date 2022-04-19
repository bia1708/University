"""
Repository which works for all existing entities
"""
import pickle


class RepositoryException(Exception):
    pass


class Repository(object):
    def __init__(self):
        self._data = {}

    def find_by_id(self, object_id):
        if object_id in self._data:
            return self._data[object_id]
        else:
            return None

    def save_to_list(self, entity):
        if self.find_by_id(entity.id):
            raise RepositoryException("The item with this ID already exists!")
        self._data[entity.id] = entity
        self._data = dict(sorted(self._data.items()))

    def update(self, entity, new_entity):
        if entity is None:
            raise RepositoryException("This item does not exist!")
        self.remove(entity.id)
        self.save_to_list(new_entity)

    def remove(self, entity_id):
        if self.find_by_id(entity_id) is None:
            raise RepositoryException(f"The item with ID {entity_id} does not exist!")
        self._data.pop(entity_id)

    def get_all(self):
        return list(self._data.values())

    def get_keys(self):
        return list(self._data.keys())

    def __len__(self):
        return len(self._data)

    def __getitem__(self, item):
        return self._data[item]


class TextFileRepository(Repository):
    def __init__(self, file_path, entity_from_line, entity_to_line):
        super().__init__()
        self.__file_path = file_path
        self.__entity_from_line = entity_from_line
        self.__entity_to_line = entity_to_line
        self.__read_from_file()

    def __read_from_file(self):
        with open(self.__file_path, 'rt') as f:
            try:
                lines = f.readlines()
                self._data.clear()
                for line in lines:
                    line = line.strip()
                    if len(line) > 0:
                        entity = self.__entity_from_line(line)
                        self._data[entity.id] = entity
            except EOFError:
                pass

    def __write_to_file(self):
        with open(self.__file_path, 'wt') as f:
            for entity_id in self._data:
                f.write(self.__entity_to_line(self._data[entity_id]) + '\n')

    def __append_to_file(self, entity):
        with open(self.__file_path, 'a') as f:
            f.write(self.__entity_to_line(entity) + '\n')

    def save_to_list(self, entity):
        self.__read_from_file()
        super().save_to_list(entity)
        self.__append_to_file(entity)

    def find_by_id(self, entity_id):
        self.__read_from_file()
        return super().find_by_id(entity_id)

    def remove(self, entity_id):
        self.__read_from_file()
        super().remove(entity_id)
        self.__write_to_file()

    def update(self, entity, new_entity):
        self.__read_from_file()
        super().update(entity, new_entity)
        self.__write_to_file()

    def __len__(self):
        self.__read_from_file()
        return super().__len__()


class BinFileRepository(Repository):
    def __init__(self, file_path, entity_from_line, entity_to_line):
        super().__init__()
        self.__file_path = file_path
        self.__entity_from_line = entity_from_line
        self.__entity_to_line = entity_to_line

    def __read_from_file(self):
        with open(self.__file_path, 'rb') as f:
            try:
                self.__data = pickle.load(f)
            except EOFError:
                pass

    def __write_to_file(self):
        with open(self.__file_path, 'wb') as f:
            pickle.dump(self.__data, f)

    def __append_to_file(self, entity):
        with open(self.__file_path, 'wb') as f:
            pickle.dump(entity, f)

    def save_to_list(self, entity):
        self.__read_from_file()
        super().save_to_list(entity)
        self.__append_to_file(entity)

    def find_by_id(self, entity_id):
        self.__read_from_file()
        return super().find_by_id(entity_id)

    def remove(self, entity_id):
        self.__read_from_file()
        super().remove(entity_id)
        self.__write_to_file()

    def update(self, entity, new_entity):
        self.__read_from_file()
        super().update(entity, new_entity)
        self.__write_to_file()

    def __len__(self):
        self.__read_from_file()
        return super().__len__()


"""

THIS ISN'T CORRECT: DON'T USE REPOS IN OTHER REPOS!!!


class ClientRentalsRepository:
    def __init__(self, client_repo, movie_repo, validator):
        self.__client_repo = client_repo
        self.__movie_repo = movie_repo
        self.__validator = validator
        self.__client_rentals = {}

    def save_to_list(self, client_id, new_rental):
        if self.__movie_repo.find_by_id(new_rental.movie_id) is None:
            raise RepositoryException("The movie you are trying to rent doesn't exist!")
        if self.__client_repo.find_by_id(client_id) is None:
            raise RepositoryException("The account you are trying to access doesn't exist!")
        self.__validator.validate(new_rental)
        if client_id not in self.__client_rentals.keys():
            self.__client_rentals[client_id] = []
        self.__client_rentals[client_id].append(new_rental)
        self.__client_rentals = dict(sorted(self.__client_rentals.items()))

    def update_rental(self, client_id, movie_id, returned_date):
        if self.__movie_repo.find_by_id(movie_id) is None:
            raise RepositoryException("The movie you are trying to return doesn't exist!")
        for rental in self.__client_rentals[client_id]:
            if rental.movie_id == movie_id:
                rental.return_date = returned_date

    def check_client_rental_status(self, client_id):
        if self.__client_repo.find_by_id(client_id) is None:
            raise RepositoryException("The account you are trying to access doesn't exist!")
        elif client_id not in self.__client_rentals.keys():
            raise RepositoryException(f"It appears that {self.__client_repo.find_by_id(client_id).name} hasn't made any"
                                      f" rentals!")

    def check_rental_possibility(self, client_id):
        today = datetime.datetime.now()
        if client_id in self.__client_rentals.keys():
            for rental in self.__client_rentals[client_id]:
                if rental.return_date is None and today > rental.due_date:
                    raise RepositoryException("You cannot rent any more movies, sorry! Please return overdue movies!")

    def get_rentals_by_id(self, id):
        return self.__client_rentals[id]

    def to_str(self, client_id):
        string = f"\n{self.__client_repo.find_by_id(client_id).name}'s rentals:\n"
        for rental in self.__client_rentals[client_id]:
            string += f"Movie: {self.__movie_repo.find_by_id(rental.movie_id).title} || "
            string += str(rental)
            string += "\n"
        return string

    def __len__(self):
        return len(self.__client_rentals)

    def __getitem__(self, item):
        return self.__client_rentals[item]
"""
