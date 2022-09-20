from random import randint

from src.domain.domain import Sentence


class Controller:
    def __init__(self, repo, validator):
        self.__repo = repo
        self.__validator = validator

    def add_sentence(self, new_sentence):
        new_sentence = Sentence(new_sentence)
        self.__validator.validate(new_sentence)
        self.__repo.save_to_list(new_sentence)

    def get_all_sentences(self):
        return self.__repo.get_all()

    def select_game_sentence(self):
        game_sentence = self.__repo[randint(0, len(self.__repo) - 1)]
        for word in game_sentence.split():
            game_sentence.find_letter(word[0])
            game_sentence.find_letter(word[len(word) - 1])

        return game_sentence

    @staticmethod
    def find_letter(letter, game_sentence):
        letter = letter.lower()
        if letter in game_sentence.sentence:
            game_sentence.find_letter(letter)
            return True
        return False

    @staticmethod
    def hangman_letter(hangman):
        for letter in hangman.sentence:
            if hangman.found[letter] == 0:
                hangman.find_letter(letter)
                break

    @staticmethod
    def game_status(game_sentence, hangman):
        if hangman.check_completed() is True:
            return 1
        elif game_sentence.check_completed() is True:
            return 2
        return 0
