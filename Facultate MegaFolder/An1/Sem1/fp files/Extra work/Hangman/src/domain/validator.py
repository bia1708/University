class SentenceException(Exception):
    pass


class SentenceValidator:
    @staticmethod
    def validate(sentence):
        words = sentence.split()
        if len(words) < 1:
            raise SentenceException("You must have at least one word!")
        for word in words:
            if len(word) < 3:
                raise SentenceException("All words need to be of minimum length 3!")