from dataclasses import dataclass


class RedoException(Exception):
    pass


@dataclass
class RedoOperation:
    target_object: object
    handler: object
    args: tuple


class RedoManager:
    __redo_operations = list()
    __iterator = -1

    @classmethod
    def check_undo_possibility(cls):
        if RedoManager.__iterator <= -1:
            return False
        return True

    @classmethod
    def register_operation(cls, target_object, handler, *args):
        cls.__redo_operations.append(RedoOperation(target_object, handler, args))

    @staticmethod
    def redo():
        if RedoManager.check_undo_possibility() is True:
            RedoManager.__iterator -= 1
            redo_operation = RedoManager.__redo_operations[RedoManager.__iterator]
            redo_operation.handler(redo_operation.target_object, *redo_operation.args)
        else:
            raise RedoException("You can't redo anymore!")

    def get_operations(self):
        return self.__redo_operations

    @staticmethod
    def increment_iterator():
        RedoManager.__iterator += 1

    @staticmethod
    def set_iterator(iterator):
        RedoManager.__iterator = iterator

