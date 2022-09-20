from src.domain.entities import Book, BookValidator


class ValidatorException(Exception):
    pass


class Validator:
    # Validator to determine whether an isbn is unique or not
    @staticmethod
    def validate_book(book, entities):
        key = int(book.isbn)
        if key in entities:
            raise ValidatorException(f"The book with the isbn {book.isbn} already exists in the list!")


class BookService:
    def __init__(self, validator1, validator2=BookValidator()):
        self.__validator1 = validator1
        self.__validator2 = validator2
        self.__data = {}

    __history_list = list()

    def add_book(self, isbn, author, title, book_dictionary):
        """
        This function adds a new book to the list
        :param book_dictionary: a dictionary containing other elements of type Book
        :param isbn: a string containing a unique book code
        :param author: a string, the author of the book
        :param title: a string, the title of the book
        :return:
        """
        book = Book(isbn, author, title)
        self.__validator2.validate(book)
        self.__validator1.validate_book(book, book_dictionary)
        isbn_code = int(book.isbn)  # TODO: get the int properly (strip string or sum)
        book_dictionary[isbn_code] = book

    def __getitem__(self, item):
        return self.__data[item]

    def display_books(self):
        for item in self.get_last:
            print(self.get_last[item])

    def get_dict(self):
        return self.__data

    @property
    def history(self):
        return self.__history_list

    def history_setter(self, new_list):
        self.__history_list.append(new_list)

    @property
    def get_last(self):
        return self.__history_list[-1]

    def remove_from_list(self):  # this will be called when we want to undo
        self.__history_list.pop(-1)

    def filter(self, title_filter):
        new_dict = {}
        for key in self.get_last:
            if self.get_last[key].title.startswith(title_filter) is False:
                new_dict[self.get_last[key].isbn] = self.get_last[key]
        self.history_setter(new_dict)

"""
class History(BookService):
    def __init__(self):
        super().__init__(Validator)
        self.__history_list = []

    @property
    def history(self):
        return self.__history_list

    @property
    def get_last(self):
        return self.__history_list[-1]

    def __getitem__(self, item):
        return self.__history_list[item]

    def add_to_list(self, book_list):
        self.__history_list.append(book_list)

    def remove_from_list(self):  # this will be called when we want to undo
        self.__history_list.pop(-1)

    def display_books(self):
        if len(self.__history_list) > 1:
            iterated_dict = self.get_last.get_dict
            for item in iterated_dict:
                print(iterated_dict[item])
        else:
            iterated_dict = self.get_last
            for item in iterated_dict:
                print(iterated_dict[item])
"""


def test_add_book():
    service = BookService(Validator)
    test_dict = service.get_dict()
    service.add_book("12", "George Orwell", "Animal Farm", test_dict)
    service.add_book("11", "J. K. Rowling", "Harry Potter", test_dict)
    assert test_dict[11].author == "J. K. Rowling"
    assert test_dict[12].title == "Animal Farm"
    try:
        service.add_book("11", "J. K. Rowling", "Harry Potter", test_dict)
        assert False
    except ValidatorException as v:
        assert str(v) == "The book with the isbn 11 already exists in the list!"


test_add_book()

