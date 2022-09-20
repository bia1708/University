"""
Repository which works for all existing entities
"""


class RepositoryException(Exception):
    pass


class Repository(object):
    def __init__(self, validator):
        self.__validator = validator
        self.__data = {}

    def find_by_id(self, object_id):
        if object_id in self.__data:
            return self.__data[object_id]
        else:
            return None

    def save_to_list(self, entity):
        self.__validator.validate(entity)
        if self.find_by_id(entity.id):
            raise RepositoryException("The item with this ID already exists!")
        self.__data[entity.id] = entity
        self.__data = dict(sorted(self.__data.items()))

    def update(self, entity, new_entity):
        if entity is None:
            raise RepositoryException("This item does not exist!")
        self.remove(entity.id)
        self.save_to_list(new_entity)

    def remove(self, entity_id):
        if self.find_by_id(entity_id) is None:
            raise RepositoryException(f"The item with ID {entity_id} does not exist!")
        self.__data.pop(entity_id)

    def get_all(self):
        return list(self.__data.values())

    def get_keys(self):
        return list(self.__data.keys())

    def __len__(self):
        return len(self.__data)

    def __getitem__(self, item):
        return self.__data[item]


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
