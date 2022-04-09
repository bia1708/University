from src.domain.domain import Sentence


class RepositoryException(Exception):
    pass


class Repository(object):
    def __init__(self):
        self._data = []

    def check_duplicate(self, sentence):
        if sentence in self._data:
            return True
        return False

    def save_to_list(self, new_sentence):
        if self.check_duplicate(new_sentence):
            raise RepositoryException("This sentence already exists!")
        self._data.append(new_sentence)

    def get_all(self):
        return list(self._data)

    def __len__(self):
        return len(self._data)

    def __getitem__(self, item):
        return self._data[item]


class TextFileRepository(Repository):
    def __init__(self, file_path):
        super().__init__()
        self.__file_path = file_path
        self.__read_from_file()

    def __read_from_file(self):
        with open(self.__file_path, 'rt') as f:
            try:
                lines = f.readlines()
                self._data.clear()
                for line in lines:
                    line = line.strip()
                    if len(line) > 0:
                        entity = Sentence(line)
                        self._data.append(entity)
            except EOFError:
                pass

    def __write_to_file(self):
        with open(self.__file_path, 'wt') as f:
            for entity in self._data:
                f.write(entity.__str__("general_access") + '\n')

    def __append_to_file(self, entity):
        with open(self.__file_path, 'a') as f:
            f.write(entity.__str__("general_access") + '\n')

    def save_to_list(self, entity):
        self.__read_from_file()
        super().save_to_list(entity)
        self.__append_to_file(entity)

    def __len__(self):
        self.__read_from_file()
        return super().__len__()
