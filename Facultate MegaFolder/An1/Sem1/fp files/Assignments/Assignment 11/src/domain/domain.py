

class Ship:
    def __init__(self, start_pos, end_pos):
        self.__start_pos = start_pos
        self.__end_pos = end_pos
        self.__tiles = []
        for x in range(self.__start_pos[0], self.__end_pos[0] + 1):
            for y in range(self.__start_pos[1], self.__end_pos[1] + 1):
                self.__tiles.append([x, y])

    def __len__(self):
        return len(self.__tiles)

    @property
    def tiles(self):
        return self.__tiles

    @property
    def starting_pos(self):
        return self.__start_pos

    @property
    def ending_pos(self):
        return self.__end_pos

    def damage_ship(self, position):
        for counter in range(len(self.__tiles) + 1):
            if self.__tiles[counter] == position:
                self.__tiles[counter] = [0]
                break

    def check_sunk(self):
        # if all the elements in this list are 0, that means our ship has sunk
        for element in self.__tiles:
            if element != [0]:
                return False
        return True


