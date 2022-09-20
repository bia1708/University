class RepositoryException(Exception):
    pass


class Repository(object):
    def __init__(self):
        self.__data = {}

    def find_by_id(self, object_id):
        if object_id in self.__data:
            return self.__data[object_id]
        else:
            return None

    def save_to_list(self, entity):
        self.__data[entity.id] = entity
        self.__data = dict(sorted(self.__data.items(), reverse=True))

    def update(self, entity, new_entity):
        if entity is None:
            raise RepositoryException("This item does not exist!")
        self.remove(entity.id)
        self.save_to_list(new_entity)

    def remove(self, entity_id):
        if self.find_by_id(entity_id) is None:
            raise RepositoryException(f"The item with ID {entity_id} does not exist!")
        self.__data.pop(entity_id)

    def get_all(self):
        return list(self.__data.values())

    def get_keys(self):
        return list(self.__data.keys())

    def __len__(self):
        return len(self.__data)

    def __getitem__(self, item):
        return self.__data[item]
