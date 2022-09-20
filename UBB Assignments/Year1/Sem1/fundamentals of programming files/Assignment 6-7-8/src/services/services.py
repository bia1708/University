import datetime
import copy
from collections import OrderedDict
from src.repository.repo import RepositoryException
from src.domain.entities import Movie, Client, Rental


class MovieService:
    def __init__(self, repo):
        self.__repo = repo

    def add_movie(self, id, title, description, genre):
        new_movie = Movie(id, title, description, genre)
        self.__repo.save_to_list(new_movie)

    def get_all_movies(self):
        return self.__repo.get_all()

    def update_movie(self, id, title, description, genre):
        old_movie = self.get_movie_by_id(id)
        new_movie = Movie(id, title, description, genre)
        self.__repo.update(old_movie, new_movie)

    def remove_movie(self, id):
        self.__repo.remove(id)

    def find_movie(self, filter):
        matches = []

        if type(filter) is not int:
            filter = filter.lower()
        for movie in self.__repo.get_all():
            if str(filter) in str(movie.id) or filter in movie.title.lower() or filter in movie.description.lower() or filter in\
                    movie.genre.lower():
                matches.append(movie)

        return matches

    def get_movie_by_id(self, id):
        for movie in self.__repo.get_all():
            if movie.id == id:
                return movie


class ClientService:
    def __init__(self, repo):
        self.__repo = repo

    def add_client(self, id, name):
        new_client = Client(id, name)
        self.__repo.save_to_list(new_client)

    def get_all_clients(self):
        return self.__repo.get_all()

    def update_client(self, id, name):
        new_client = Client(id, name)
        old_client = self.get_client_by_id(id)
        self.__repo.update(old_client, new_client)

    def remove_client(self, id):
        self.__repo.remove(id)

    def find_client(self, filter):
        matches = []

        if type(filter) is not int:
            filter = filter.lower()
        for client in self.__repo.get_all():
            if str(filter) in str(client.id) or filter in client.name.lower():
                matches.append(client)

        return matches

    def get_client_by_id(self, id):
        for client in self.__repo.get_all():
            if client.id == id:
                return client


class RentalService:
    def __init__(self, repo, client_repo, movie_repo):
        self.__repo = repo
        self.__client_repo = client_repo
        self.__movie_repo = movie_repo

    number_of_rentals = 0

    def get_rentals_by_client_id(self, client_id):
        client_rentals = []
        for rental in self.__repo.get_all():
            if rental.client_id == client_id:
                client_rentals.append(rental)
        return client_rentals

    """
    def get_rentals_by_movie_id(self, movie_id):
        movie_rentals = []
        for rental in self.__repo.get_all():
            if rental.movie_id == movie_id:
                movie_rentals.append(rental)
        return movie_rentals
    """

    def get_last_client_rental_by_movie_id(self, movie_id, client_id):
        last_rental = None
        for rental in self.__repo.get_all():
            # this loop will get the last rental for this movie
            if rental.movie_id == movie_id and rental.client_id == client_id:
                last_rental = rental
        return last_rental

    @staticmethod
    def get_days_rented(rental):
        days = 0
        today = datetime.datetime.now()
        if rental.return_date is None:
            days += (today - rental.rental_date).days
        else:
            days += (rental.return_date - rental.rental_date).days

        return days

    @staticmethod
    def get_past_due_days(rental):
        days = 0
        today = datetime.datetime.now()
        if rental.return_date is not None and rental.return_date > rental.due_date:
            days += (rental.return_date - rental.due_date).days
        elif rental.return_date is None and today > rental.due_date:
            days += (today - rental.due_date).days
        return days

    def check_rental_possibility(self, client_id):
        today = datetime.datetime.now()
        if client_id in self.__client_repo.get_keys():
            for rental in self.get_rentals_by_client_id(client_id):
                if rental.return_date is None and today > rental.due_date:
                    raise RepositoryException("You cannot rent any more movies, sorry! Please return overdue movies!")

    def check_obj_existence(self, client_id, movie_id):
        if self.__client_repo.find_by_id(client_id) is None:
            raise RepositoryException("The account you are trying to access doesn't exist!")
        elif self.__movie_repo.find_by_id(movie_id) is None:
            raise RepositoryException("The movie you are trying to access doesn't exist!")

    def check_client_rental_status(self, client_id, movie_id):
        if len(self.get_rentals_by_client_id(client_id)) == 0:
            raise RepositoryException(f"It appears that {self.__client_repo.find_by_id(client_id).name} hasn't made any"
                                      f" rentals!")
        elif self.get_last_client_rental_by_movie_id(movie_id, client_id) is None:
            raise RepositoryException(f"You haven't rented {self.__movie_repo.find_by_id(movie_id).title} yet!")

    def rent_movie(self, movie_id, client_id, rental_date):
        self.check_obj_existence(client_id, movie_id)
        self.check_rental_possibility(client_id)
        self.number_of_rentals += 1

        # If we don't specify a rental date, it will be automatically set to today's date
        if rental_date is None:
            rental_date = datetime.datetime.now()
        else:
            rental_date = datetime.datetime.strptime(rental_date, "%d-%m-%Y")

        # The due date will be automatically set to today's date + 30 days
        due_date = copy.deepcopy(rental_date)
        due_date += datetime.timedelta(days=30)

        new_rental = Rental(self.number_of_rentals, movie_id, client_id, rental_date, due_date)

        self.__repo.save_to_list(new_rental)

    def remove_rental(self, id):
        self.__repo.remove(id)

    def return_movie(self, movie_id, client_id, return_date):
        self.check_obj_existence(client_id, movie_id)
        self.check_client_rental_status(client_id, movie_id)

        # If we don't specify a return date, it will be automatically set to today's date
        if return_date is None:
            return_date = datetime.datetime.now()
        else:
            return_date = datetime.datetime.strptime(return_date, "%d-%m-%Y")

        old_rental = self.get_last_client_rental_by_movie_id(movie_id, client_id)
        if old_rental.return_date is not None:
            raise RepositoryException("You have already returned this movie!")
        else:
            new_rental = copy.deepcopy(old_rental)
            new_rental.return_date = return_date

            self.__repo.update(old_rental, new_rental)

    def reverse_return_movie(self, movie_id, client_id):
        old_rental = self.get_last_client_rental_by_movie_id(movie_id, client_id)

        new_rental = copy.deepcopy(old_rental)
        new_rental.return_date = None

        self.__repo.update(old_rental, new_rental)

    def most_rented_movies(self):
        # This dict saves the number of days rented for each movie. The keys are the movie IDs.
        rented_stats = {}

        for movie_id in self.__movie_repo.get_keys():
            rented_stats[movie_id] = 0

        for rental in self.__repo.get_all():
            rented_stats[rental.movie_id] += self.get_days_rented(rental)

        rented_stats = OrderedDict(sorted(rented_stats.items(), key=lambda kv: (kv[1], kv[0]), reverse=True))
        return rented_stats

    def most_active_clients(self):
        # This dict saves the activity for each client. The keys are the client IDs.
        client_activity = {}

        for client_id in self.__client_repo.get_keys():
            client_activity[client_id] = 0

        for rental in self.__repo.get_all():
            client_activity[rental.client_id] += self.get_days_rented(rental)

        client_activity = OrderedDict(sorted(client_activity.items(), key=lambda kv: (kv[1], kv[0]), reverse=True))
        return client_activity

    def late_rentals(self):
        # This dict saves the number of days past the due date for each movie rented. The keys are the movie IDs.
        late_rentals = {}

        for movie_id in self.__movie_repo.get_keys():
            late_rentals[movie_id] = 0

        for rental in self.__repo.get_all():
            late_rentals[rental.movie_id] += self.get_past_due_days(rental)

        late_rentals = OrderedDict(sorted(late_rentals.items(), key=lambda kv: (kv[1], kv[0]), reverse=True))
        return late_rentals
