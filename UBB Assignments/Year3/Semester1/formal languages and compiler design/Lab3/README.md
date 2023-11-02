## [Lab3](https://github.com/bia1708/University/tree/flcd/UBB%20Assignments/Year3/Semester1/formal%20languages%20and%20compiler%20design/Lab3)

## Dependencies
This project requires the `tabulate` python package:
- `python -m pip install tabulate`
---
The `Scanner` class is designed for lexical analysis of a given problem text. It tokenizes the input text, generates a Program Internal Form (PIF), and maintains a Symbol Table (ST) for identifiers and constants.

## Attributes

- `__tokens` (list): List of reserved tokens.
- `__symbol_table` (SymbolTable): Symbol Table instance for storing identifiers and constants.
- `__pif` (list): Program Internal Form for tokenized input.
- `__problem_text` (list): List of lines from the problem text.

## Methods

1.  `__init__(self, problem)`: Initialize the `Scanner` class with a given problem text.

    #### Parameters:
    - `problem` (str): The path to the problem text file.
  
<br>

2. `__scan(self)`: Tokenize the problem text, populate the PIF, and handle lexical errors.

<br>

3.  `breakup_line(line)`: Split a line into individual words, taking delimiters into account.

    #### Parameters
    - `line` (str): The input line to be split.

    #### Returns
    - `list`: A list of words extracted from the input line.

<br>

4. `write_files(self)`: Write the PIF and Symbol Table to output files.
---
### Input files:
- `tokens.in`
<br>

### Output files:
- `PIF.out`
- `ST.out`
