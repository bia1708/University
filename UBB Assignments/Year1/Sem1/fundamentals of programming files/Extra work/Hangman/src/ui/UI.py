from src.domain.domain import Sentence
from src.domain.validator import SentenceException
from src.repository.repo import RepositoryException


class Console:
    def __init__(self, controller):
        self.__controller = controller

    @staticmethod
    def print_menu():
        print("\nWelcome to Hangman!")
        print("What would you like to do today?\n"
              "\t1. Add a new sentence\n"
              "\t2. Print sentences\n"
              "\t3. Start a new game\n"
              "\t'x' exits the program\n")

    def print_sentences(self):
        for sentence in self.__controller.get_all_sentences():
            print(sentence.__str__("general_access"))

    def ui_add_sentence(self):
        new_sentence = input("Your sentence: ")
        try:
            self.__controller.add_sentence(new_sentence)
        except SentenceException as se:
            print(se)
        except RepositoryException as re:
            print(re)

    def ui_play_game(self):
        print("NEW GAME\n")
        game_sentence = self.__controller.select_game_sentence()
        hangman = Sentence("hangman")
        chosen_letters = []

        while self.__controller.game_status(game_sentence, hangman) == 0:
            print(game_sentence)
            user_choice = input("Choose a letter: ")
            if self.__controller.find_letter(user_choice, game_sentence) is False or user_choice in chosen_letters:
                self.__controller.hangman_letter(hangman)
            chosen_letters.append(user_choice)
            print("Hangman: ", hangman, "\n")

        if self.__controller.game_status(game_sentence, hangman) == 1:
            print(f"You LOST!\nThe sentence was <<{game_sentence.__str__('general_access')}>>")
        else:
            print(f"You WON!\nThe sentence was <<{game_sentence.__str__('general_access')}>>")

    def run_game(self):
        commands = {
            "1": self.ui_add_sentence,
            "2": self.print_sentences,
            "3": self.ui_play_game
        }
        while True:
            self.print_menu()
            cmd = input("Your option: ")
            if cmd == 'x':
                break
            else:
                try:
                    commands[cmd]()
                except KeyError as ke:
                    print(str(ke) + "is not a valid command! Please try again!")
