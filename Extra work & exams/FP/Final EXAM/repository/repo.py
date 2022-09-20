class RepositoryException(Exception):
    pass


class Repository(object):
    def __init__(self):
        self._data = {}

    def find_by_id(self, object_id):
        """
        This function finds an object by its id
        :param object_id:
        :return:
        """
        if object_id in self._data:
            return self._data[object_id]
        else:
            return None

    def save_to_list(self, entity):
        """
        This function saves an entity to the list
        :param entity:
        :return:
        """
        if self.find_by_id(entity.id):
            raise RepositoryException("The item with this ID already exists!")
        self._data[entity.id] = entity
        self._data = dict(sorted(self._data.items()))

    def update(self, entity, new_entity):
        """
        This function updates an existing entity
        :param entity:
        :param new_entity:
        :return:
        """
        if entity is None:
            raise RepositoryException("This item does not exist!")
        self.remove(entity.id)
        self.save_to_list(new_entity)

    def remove(self, entity_id):
        """
        This function removes an existing entity
        :param entity_id:
        :return:
        """
        if self.find_by_id(entity_id) is None:
            raise RepositoryException(f"The item with ID {entity_id} does not exist!")
        self._data.pop(entity_id)

    def get_all(self):
        return list(self._data.values())

    def get_keys(self):
        return list(self._data.keys())

    def __len__(self):
        return len(self._data)

    def __getitem__(self, item):
        return self._data[item]


class TextFileRepository(Repository):
    def __init__(self, file_path, entity_from_line, entity_to_line):
        super().__init__()
        self.__file_path = file_path
        self.__entity_from_line = entity_from_line
        self.__entity_to_line = entity_to_line
        self.__read_from_file()

    def __read_from_file(self):
        with open(self.__file_path, 'rt') as f:
            try:
                lines = f.readlines()
                self._data.clear()
                for line in lines:
                    line = line.strip()
                    if len(line) > 0:
                        entity = self.__entity_from_line(line)
                        self._data[entity.id] = entity
            except EOFError:
                pass

    def __write_to_file(self):
        with open(self.__file_path, 'wt') as f:
            for entity_id in self._data:
                f.write(self.__entity_to_line(self._data[entity_id]) + '\n')

    def __append_to_file(self, entity):
        with open(self.__file_path, 'a') as f:
            f.write(self.__entity_to_line(entity) + '\n')

    def save_to_list(self, entity):
        self.__read_from_file()
        super().save_to_list(entity)
        self.__append_to_file(entity)

    def find_by_id(self, entity_id):
        self.__read_from_file()
        return super().find_by_id(entity_id)

    def remove(self, entity_id):
        self.__read_from_file()
        super().remove(entity_id)
        self.__write_to_file()

    def update(self, entity, new_entity):
        self.__read_from_file()
        super().update(entity, new_entity)
        self.__write_to_file()

    def __len__(self):
        self.__read_from_file()
        return super().__len__()

