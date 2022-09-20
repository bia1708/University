
# This file contains the entities required to manage a bookstore

class BookValidatorException(Exception):
    pass


class BookValidator:
    def validate(self, book):
        if book.isbn.isdigit() is not True:
            raise BookValidatorException("Invalid isbn!")
        if any(char.isdigit() for char in book.author):
            raise BookValidatorException("Invalid author name!")


class Book:
    def __init__(self, isbn, author, title):
        self.__isbn = isbn
        self.__author = author
        self.__title = title

    @property
    def isbn(self):
        return self.__isbn

    @isbn.setter
    def isbn(self, new_isbn):
        self.__isbn = new_isbn

    @property
    def author(self):
        return self.__author

    @author.setter
    def author(self, new_author):
        self.__author = new_author

    @property
    def title(self):
        return self.__title

    def __str__(self):
        representation = f"Isbn: {self.isbn} || Author: {self.author} || Title: {self.title}"
        return representation


def test_book():
    book = Book("1", "Karen McManus", "One of Us is Lying")
    assert book.isbn == "1"
    assert book.author == "Karen McManus"
    assert book.title == "One of Us is Lying"


test_book()
