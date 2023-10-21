## [Lab2](https://github.com/bia1708/University/tree/flcd/UBB%20Assignments/Year3/Semester1/formal%20languages%20and%20compiler%20design/Lab2)

A SymbolTable class for storing symbols using a hash table.

Attributes:
- size: The size of the hash table.
- table: A list of lists, representing the hash table.

Methods:
- __init__(self, size): Constructor that initializes the symbol table with a specified size.
- get_size(self): Returns the size of the symbol table.
- __hash(self, key): Private method for computing the hash value of a key.
- add(self, key): Adds a key to the symbol table.
- remove(self, key): Removes a key from the symbol table.
- contains(self, key): Checks if a key is present in the symbol table.
- get_index(self, value): Retrieves the index of a value in the symbol table.
- __str__(self): Returns a string representation of the symbol table for debugging and printing.
