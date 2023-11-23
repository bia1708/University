from tabulate import tabulate

class SymbolTable:
    def __init__(self, size):
        self.size = size
        self.table = []

        for index in range(size):
            self.table.append([])

    def get_size(self):
        return self.size

    def __hash(self, key):
        # hash function which sums up all ascii codes of characters and calculates pos
        sum = 0
        for char in str(key):
            sum += ord(char.lower())
        return sum % self.size

    def add(self, key):
        hash_value = self.__hash(key)  # calculate pos for the key to be added
        if key not in self.table[hash_value]:
            self.table[hash_value].append(key)  # add key to its respective bucket in the hash table (separate chaining)
        return hash_value, self.table[hash_value].index(key)

    def remove(self, key):
        hash_value = self.__hash(key)
        if key in self.table[hash_value]:
            self.table[hash_value].remove(key)  # remove key from bucket

    def contains(self, key):
        hash_value = self.__hash(key)
        return key in self.table[hash_value]  # check if key is in its supposed bucket

    def get_index(self, value):
        key = self.__hash(value)
        return self.table[key].index(value)  # get pos in bucket of element

    def __str__(self):
        headers = ["Index", "Value"]
        data = []
        for i in range(self.size):
            for keyword in self.table[i]:
                data.append([f"({i}, {self.get_index(keyword)})", keyword])
        return tabulate(data, headers, tablefmt="grid")
