from dataclasses import dataclass


class UndoException(Exception):
    pass


@dataclass
class UndoOperation:
    target_object: object
    handler: object
    args: tuple


class UndoManager:
    __undo_operations = []
    __iterator = -1

    @classmethod
    def check_undo_possibility(cls):
        if cls.__iterator == -1:
            return False
        return True

    @classmethod
    def register_operation(cls, target_object, handler, *args):
        cls.__undo_operations.append(UndoOperation(target_object, handler, args))
        cls.__iterator += 1

    @staticmethod
    def undo():
        if UndoManager.check_undo_possibility() is True:
            undo_operation = UndoManager.__undo_operations[UndoManager.__iterator]
            UndoManager.__iterator -= 1
            undo_operation.handler(undo_operation.target_object, *undo_operation.args)
        else:
            raise UndoException("You can't undo anymore!")

    def get_operations(self):
        return self.__undo_operations

    @staticmethod
    def increment_iterator():
        UndoManager.__iterator += 1

    @staticmethod
    def get_iterator():
        return UndoManager.__iterator

    @staticmethod
    def reset_stack():
        UndoManager.__undo_operations.clear()
        UndoManager.__iterator = -1