from src.domain.validators import StoreExceptions
from src.repository.repo import RepositoryException
from src.services.handlers import UndoHandler, RedoHandler
from src.services.undo_manager import UndoManager, UndoException
from src.services.redo__manager import RedoManager, RedoException


class Console:
    def __init__(self, movie_service, client_service, rental_service):
        self.__movie_service = movie_service
        self.__client_service = client_service
        self.__rental_service = rental_service

    @staticmethod
    def print_menu():
        print("\nHello! What would you like to do today?")
        print("MOVIE OPTIONS:\n"
              "\t1. List all the movies\n"
              "\t2. Search movie\n"
              "\t3. Add a new movie\n"
              "\t4. Remove a movie\n"
              "\t5. Update a movie\n"
              "CLIENT OPTIONS:\n"
              "\t6. List all the clients\n"
              "\t7. Search client\n"
              "\t8. Add a new client\n"
              "\t9. Remove a client\n"
              "\t10. Update a client\n"
              "RENTAL SERVICE:\n"
              "\t11. List rentals for a certain client\n"
              "\t12. Rent a movie\n"
              "\t13. Return a movie\n"
              "STATISTICS:\n"
              "\t14. Most rented movies\n"
              "\t15. Most active clients\n"
              "\t16. Late rentals"
              "\nUndo: u\n"
              "Redo: r\n"
              "Exit: x\n")

    def populate_list_movies(self):
        self.__movie_service.add_movie(1, "Atonement", "Thirteen-year-old fledgling writer Briony Tallis irrevocably "
                                                       "changes the course of several lives when she accuses her "
                                                       "older sister's lover of a crime he did not commit.", "Romance")
        self.__movie_service.add_movie(2, "A Beautiful Mind", "After John Nash, a brilliant but asocial "
                                                              "mathematician, accepts secret work in cryptography, "
                                                              "his life takes a turn for the nightmarish.", "Drama")
        self.__movie_service.add_movie(3, "Dune", "Feature adaptation of Frank Herbert's science fiction novel, "
                                                  "about the son of a noble family entrusted with the protection of "
                                                  "the most valuable asset and most vital element in the galaxy.",
                                       "Action")
        self.__movie_service.add_movie(4, "Fight Club", "An insomniac office worker and a devil-may-care soap maker "
                                                        "form an underground fight club that evolves into much more.",
                                       "Drama")
        self.__movie_service.add_movie(5, "Gladiator", "A former Roman General sets out to exact vengeance against "
                                                       "the corrupt emperor who murdered his family and sent him into"
                                                       " slavery.", "Drama")
        self.__movie_service.add_movie(6, "How to Lose a Guy in 10 Days", "Benjamin Barry is an advertising executive "
                                                                          "and ladies' man who, to win a big "
                                                                          "campaign, bets that he can make a woman "
                                                                          "fall in love with him in 10 days.", "Comedy")
        self.__movie_service.add_movie(7, "Inglorious Basterds", "In Nazi-occupied France during World War II, a plan "
                                                                 "to assassinate Nazi leaders by a group of Jewish "
                                                                 "U.S. soldiers coincides with a theatre owner's "
                                                                 "vengeful plans for the same.", "Action")
        self.__movie_service.add_movie(8, "Interstellar", "A team of explorers travel through a wormhole in space in "
                                                          "an attempt to ensure humanity's survival.", "Sci-Fi")
        self.__movie_service.add_movie(9, "Se7en", "Two detectives, a rookie and a veteran, hunt a serial killer who "
                                                   "uses the seven deadly sins as his motives.", "Mystery")
        self.__movie_service.add_movie(10, "The Good, the Bad and the Ugly", "A bounty hunting scam joins two men in "
                                                                             "an uneasy alliance against a third in a "
                                                                             "race to find a fortune in gold buried in "
                                                                             "a remote cemetery.", "Western")

    def populate_list_clients(self):
        self.__client_service.add_client(1, "Aaron Paul")
        self.__client_service.add_client(2, "Elijah Wood")
        self.__client_service.add_client(3, "Queen Elizabeth")
        self.__client_service.add_client(4, "Shrek")
        self.__client_service.add_client(5, "Jimmy Kimmel")
        self.__client_service.add_client(6, "Mike Myers")
        self.__client_service.add_client(7, "Anna Wintour")
        self.__client_service.add_client(8, "Ricky Gervais")
        self.__client_service.add_client(9, "Martha Stewart")
        self.__client_service.add_client(10, "Dolores Umbridge")

    def populate_rental_list(self):
        self.__rental_service.rent_movie(2, 3, "12-03-2021")
        self.__rental_service.rent_movie(2, 1, "15-11-2021")
        self.__rental_service.rent_movie(6, 5, "17-10-2021")

    def populate(self):
        self.populate_list_movies()
        self.populate_list_clients()
        self.populate_rental_list()

    def ui_list_movies(self):
        for movie in self.__movie_service.get_all_movies():
            print(movie)

    def ui_filter_movie(self):
        filter = input("Search: ")
        matches = self.__movie_service.find_movie(filter)
        for match in matches:
            print(match)

    def ui_add_movie(self):
        id = input("ID: ")
        title = input("Title: ")
        description = input("Description: ")
        genre = input("Genre: ")
        try:
            id = int(id)
            self.__movie_service.add_movie(id, title, description, genre)
            UndoManager.register_operation(self.__movie_service, UndoHandler.ADD_MOVIE, id)
            RedoManager.register_operation(self.__movie_service, RedoHandler.ADD_MOVIE, id, title, description, genre)
        except ValueError:
            print("Please enter a valid ID!")
        except StoreExceptions as se:
            print(se)
        except RepositoryException as re:
            print(re)

    def ui_remove_movie(self):
        id = input("ID: ")
        try:
            id = int(id)
            movie = self.__movie_service.get_movie_by_id(id)
            self.__movie_service.remove_movie(id)
            UndoManager.register_operation(self.__movie_service, UndoHandler.DELETE_MOVIE, id, movie.title,
                                           movie.description, movie.genre)
            RedoManager.register_operation(self.__movie_service, RedoHandler.DELETE_MOVIE, id)
        except ValueError:
            print("Please enter a valid ID!")
        except RepositoryException as re:
            print(re)

    def ui_update_movie(self):
        id = input("ID: ")
        title = input("Title: ")
        description = input("Description: ")
        genre = input("Genre: ")
        try:
            id = int(id)
            movie = self.__movie_service.get_movie_by_id(id)
            self.__movie_service.update_movie(id, title, description, genre)
            UndoManager.register_operation(self.__movie_service, UndoHandler.UPDATE_MOVIE, id, movie.title,
                                           movie.description, movie.genre)
            RedoManager.register_operation(self.__movie_service, RedoHandler.UPDATE_MOVIE, id, title, description, genre)
        except ValueError:
            print("Please enter a valid ID!")
        except StoreExceptions as se:
            print(se)
        except RepositoryException as re:
            print(re)

    def ui_list_clients(self):
        for client in self.__client_service.get_all_clients():
            print(client)

    def ui_filter_clients(self):
        filter = input("Search: ")
        matches = self.__client_service.find_client(filter)
        for match in matches:
            print(match)

    def ui_add_client(self):
        id = input("ID: ")
        name = input("Name: ")
        try:
            id = int(id)
            self.__client_service.add_client(id, name)
            UndoManager.register_operation(self.__client_service, UndoHandler.ADD_CLIENT, id)
            RedoManager.register_operation(self.__client_service, RedoHandler.ADD_CLIENT, id, name)
        except ValueError:
            print("Please enter a valid ID!")
        except StoreExceptions as se:
            print(se)
        except RepositoryException as re:
            print(re)

    def ui_remove_client(self):
        id = input("ID: ")
        try:
            id = int(id)
            client = self.__client_service.get_client_by_id(id)
            UndoManager.register_operation(self.__client_service, UndoHandler.REMOVE_CLIENT, id, client.name)
            RedoManager.register_operation(self.__client_service, RedoHandler.REMOVE_CLIENT, id)
            self.__client_service.remove_client(id)
        except ValueError:
            print("Please enter a valid ID!")
        except RepositoryException as re:
            print(re)

    def ui_update_client(self):
        id = input("ID: ")
        name = input("Name: ")
        try:
            id = int(id)
            client = self.__client_service.get_client_by_id(id)
            UndoManager.register_operation(self.__client_service, UndoHandler.UPDATE_CLIENT, id, client.name)
            RedoManager.register_operation(self.__client_service, RedoHandler.UPDATE_CLIENT, id, name)
            self.__client_service.update_client(id, name)
        except ValueError:
            print("Please enter a valid ID!")
        except StoreExceptions as se:
            print(se)
        except RepositoryException as re:
            print(re)

    def ui_list_rentals(self):
        id = input("Client ID: ")
        try:
            id = int(id)
            # TODO: try except for when the client doesnt exist
            # TODO: print sth else when the client has no rentals
            client_name = self.__client_service.get_client_by_id(id).name
            print(f"\n{client_name}'s rentals:")
            for rental in self.__rental_service.get_rentals_by_client_id(id):
                movie = self.__movie_service.get_movie_by_id(rental.movie_id)
                print("Movie: ", movie.title, "|| ", rental)
        except ValueError:
            print("Please enter a valid ID!")
        except RepositoryException as re:
            print(re)

    def ui_rent_movie(self):
        client_id = input("Client ID: ")
        movie_id = input("Movie ID: ")
        rental_date = None
        choice = input("Do you want to specify the rental date? (default date will be set to current date): ")
        if choice == "yes":
            rental_date = input("Rental Date: ")
        try:
            movie_id = int(movie_id)
            client_id = int(client_id)
        except ValueError:
            print("Please enter a valid ID!")

        try:
            self.__rental_service.rent_movie(movie_id, client_id, rental_date)
            UndoManager.register_operation(self.__rental_service, UndoHandler.ADD_RENTAL,
                                           self.__rental_service.number_of_rentals)
            RedoManager.register_operation(self.__rental_service, RedoHandler.ADD_RENTAL,
                                           client_id, movie_id, rental_date)
        except ValueError:
            print("Please enter a valid date!")
        except RepositoryException as re:
            print(re)
        except StoreExceptions as se:
            print(se)

    def ui_return_movie(self):
        client_id = input("Client ID: ")
        movie_id = input("Movie ID: ")
        return_date = None
        choice = input("Do you want to specify the return date? (default date will be set to current date): ")
        if choice == "yes":
            return_date = input("Return Date: ")
        try:
            movie_id = int(movie_id)
            client_id = int(client_id)
        except ValueError:
            print("Please enter a valid ID!")
        try:
            self.__rental_service.return_movie(movie_id, client_id, return_date)
            UndoManager.register_operation(self.__rental_service, UndoHandler.RETURN_MOVIE, movie_id, client_id)
            RedoManager.register_operation(self.__rental_service, RedoHandler.RETURN_MOVIE, movie_id, client_id, return_date)
        except ValueError:
            print("Please enter a valid date!")
        except RepositoryException as re:
            print(re)
        except StoreExceptions as se:
            print(se)

    def ui_most_rented_movies(self):
        most_rented = self.__rental_service.most_rented_movies()
        print("\nMost rented movies:")
        for id in most_rented.keys():
            if most_rented[id] != 0:
                print("\t->", self.__movie_service.get_movie_by_id(id).title, ": ", most_rented[id], "days rented")

    def ui_most_active_clients(self):
        client_activity = self.__rental_service.most_active_clients()
        print("\nMost active clients:")
        for id in client_activity.keys():
            if client_activity[id] != 0:
                print("\t->", self.__client_service.get_client_by_id(id).name, ": ", client_activity[id],
                      "activity points")

    def ui_late_rentals(self):
        late_rentals = self.__rental_service.late_rentals()
        print("\nLate rentals:")
        for id in late_rentals.keys():
            if late_rentals[id] != 0:
                print("\t->", self.__movie_service.get_movie_by_id(id).title, ": ", late_rentals[id],
                      "days past due date")

    @staticmethod
    def ui_undo():
        try:
            UndoManager.undo()
            RedoManager.increment_iterator()
        except UndoException as ue:
            print(ue)

    @staticmethod
    def ui_redo():
        try:
            RedoManager.redo()
            UndoManager.increment_iterator()
        except RedoException as re:
            print(re)

    def startup(self):
        commands = {
            "1": self.ui_list_movies,
            "2": self.ui_filter_movie,
            "3": self.ui_add_movie,
            "4": self.ui_remove_movie,
            "5": self.ui_update_movie,
            "6": self.ui_list_clients,
            "7": self.ui_filter_clients,
            "8": self.ui_add_client,
            "9": self.ui_remove_client,
            "10": self.ui_update_client,
            "11": self.ui_list_rentals,
            "12": self.ui_rent_movie,
            "13": self.ui_return_movie,
            "14": self.ui_most_rented_movies,
            "15": self.ui_most_active_clients,
            "16": self.ui_late_rentals,
            "u": self.ui_undo,
            "r": self.ui_redo
        }


        while True:
            Console.print_menu()
            cmd = input("Option: ")
            if cmd == "x":
                break
            else:
                try:
                    commands[cmd]()
                except KeyError as ke:
                    print(str(ke) + "is not a valid command! Please try again!")







"""
1, 2, 3, 12-03-2021, 11-04-2021
2, 2, 1, 15-11-2021, 15-12-2021
3, 6, 5, 17-10-2021, 17-11-2021

"""