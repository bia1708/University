"""
Write an application for movie rentals. The application will store:

Movie: rental_id, name, description, genre
Client: client_id, name
Rental: rental_id, rental_id, client_id, rented_date, due_date, returned_date
"""
import textwrap


class Movie:
    def __init__(self, id, title, description, genre):
        self.__id = id
        self.__title = title
        self.__description = description
        self.__genre = genre

    @property
    def id(self):
        return self.__id

    @property
    def title(self):
        return self.__title

    @title.setter
    def title(self, value):
        self.__title = value

    @property
    def description(self):
        return self.__description

    @description.setter
    def description(self, value):
        self.__description = value

    @property
    def genre(self):
        return self.__genre

    @genre.setter
    def genre(self, value):
        self.__genre = value

    def __str__(self):
        string = f"ID: {self.__id} || Movie: {self.__title} || Genre: {self.__genre}\n"
        description = f"\t-> Description: {self.__description}"
        new = textwrap.fill(description, subsequent_indent="\t\t\t\t\t", width=170)
        string += new
        return string


class Client:
    def __init__(self, id, name):
        self.__client_id = id
        self.__name = name

    @property
    def id(self):
        return self.__client_id

    @property
    def name(self):
        return self.__name

    @name.setter
    def name(self, value):
        self.__name = value

    def __str__(self):
        string = f"ID: {self.__client_id} || Name: {self.__name}"
        return string


class Rental:
    def __init__(self, id, movie_id, client_id, rental_date, due_date, return_date=None):
        self.__rental_id = id
        self.__movie_id = movie_id
        self.__client_id = client_id
        self.__rental_date = rental_date
        self.__due_date = due_date
        self.__return_date = return_date

    @property
    def id(self):
        return self.__rental_id

    @property
    def movie_id(self):
        return self.__movie_id

    @movie_id.setter
    def movie_id(self, value):
        self.__movie_id = value

    @property
    def client_id(self):
        return self.__client_id

    @client_id.setter
    def client_id(self, value):
        self.__client_id = value

    @property
    def rental_date(self):
        return self.__rental_date

    @rental_date.setter
    def rental_date(self, value):
        self.__rental_date = value

    @property
    def due_date(self):
        return self.__due_date

    @due_date.setter
    def due_date(self, value):
        self.__due_date = value

    @property
    def return_date(self):
        return self.__return_date

    @return_date.setter
    def return_date(self, value):
        self.__return_date = value

    def __str__(self):
        string = f"Rental Date: {self.__rental_date.strftime('%d-%m-%Y')} || Due Date: {self.__due_date.strftime('%d-%m-%Y')}"
        if self.__return_date is None:
            string += "\n\t-> This movie hasn't been returned yet!"
        else:
            string += f" || Return Date: {self.__return_date.strftime('%d-%m-%Y')}"
        return string

