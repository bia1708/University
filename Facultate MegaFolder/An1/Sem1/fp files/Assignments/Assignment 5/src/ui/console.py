from src.services.book_service import ValidatorException, BookService
from src.domain.entities import BookValidatorException
from copy import deepcopy


class Console:
    def __init__(self, book_service):
        self.__book_service = book_service

    def print_menu(self):
        print("\nWelcome to your library! What would you like to do today?"
              "\n1. Add a new book to the list."
              "\n2. Display all the books in the library."
              "\n3. Filter the list by title."
              "\n4. Undo the last operation."
              "\n Press 'x' to exit the program.")

    def populate_list(self):
        self.__book_service.add_book("1", "William Gibson", "Neuromancer", self.__book_service.get_dict())
        self.__book_service.add_book("2", "Mark Z. Danielewski", "House of Leaves", self.__book_service.get_dict())
        self.__book_service.add_book("3", "Philip K. Dick", "Do Androids Dream of Electric Sheep?", self.__book_service.get_dict())
        self.__book_service.add_book("4", "Douglas Adams", "The Hitchhiker's Guide to the Galaxy", self.__book_service.get_dict())
        self.__book_service.add_book("5", "Frank Herbert", "Dune", self.__book_service.get_dict())
        self.__book_service.add_book("6", "Andy Weir", "Andy Weir", self.__book_service.get_dict())
        self.__book_service.add_book("7", "Karen M. McManus", "One of Us is Lying", self.__book_service.get_dict())
        self.__book_service.add_book("8", "Dmitri Gluhovski", "Metro 2033", self.__book_service.get_dict())
        self.__book_service.add_book("9", "Max Brooks", "World War Z", self.__book_service.get_dict())
        self.__book_service.add_book("10", "William Golding", "Lord of the Flies", self.__book_service.get_dict())
        BookService.history_setter(self.__book_service, self.__book_service.get_dict())

    def ui_add_function(self):
        print("Type in x to stop adding!")
        new_dict = deepcopy(self.__book_service.get_last)
        did_operation = 0  # we check that the element was actually added
        while True:
            isbn = input("Isbn: ")
            author = input("Author: ")
            title = input("Title: ")
            try:
                self.__book_service.add_book(isbn, author, title, new_dict)
                did_operation = 1
            except BookValidatorException as be:
                print(be)
            except ValidatorException as ve:
                print(ve)

            cmd = input()
            if cmd == "x":
                break
        if did_operation == 1:
            BookService.history_setter(self.__book_service, new_dict)

    def ui_display_books(self):
        self.__book_service.display_books()

    def ui_undo(self):
        if len(self.__book_service.history) > 1:
            self.__book_service.remove_from_list()
        else:
            print("You cannot undo anymore!")

    def ui_filter_by_title(self):
        title_filter = input("Type in you filter: ")
        BookService.filter(self.__book_service, title_filter)

    def run_console(self):
        commands = {
            "1": self. ui_add_function,
            "2": self.ui_display_books,
            "3": self.ui_filter_by_title,
            "4": self.ui_undo
        }
        self.populate_list()

        while True:
            Console.print_menu(self)
            cmd = input("Option: ")
            if cmd == "x":
                break
            else:
                try:
                    commands[cmd]()
                except KeyError as ke:
                    print(str(ke) + "is not a valid command! Please try again!")
