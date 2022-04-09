class Sentence:
    def __init__(self, string):
        self.__sentence = string.lower()
        self.__found = {}
        for letter in self.__sentence:
            self.__found[letter] = 0

    @property
    def sentence(self):
        return self.__sentence

    @sentence.setter
    def sentence(self, value):
        self.__sentence = value

    @property
    def found(self):
        return self.__found

    def find_letter(self, letter):
        self.__found[letter] = 1

    def __str__(self, mode=None):
        string = ""
        if mode == "general_access":
            string += self.__sentence
        else:
            for letter in self.__sentence:
                if letter == " ":
                    string += " "
                elif self.__found[letter] == 0:
                    string += "_"
                else:
                    string += letter
        return string

    def split(self):
        return self.__sentence.split()

    def check_completed(self):
        for letter in self.__found.keys():
            if self.__found[letter] == 0 and letter != " ":
                return False
        return True
