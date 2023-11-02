import re
import sys

from ST import SymbolTable
from tabulate import tabulate


class Scanner:
    def __init__(self, problem):
        with open("tokens.in") as file:
            self.__tokens = [line.strip() for line in file.readlines()]
        self.__symbol_table = SymbolTable(20)
        self.__pif = []
        with open(problem) as file:
            self.__problem_text = file.readlines()
        self.__scan()

    def __scan(self):
        for index, line in enumerate(self.__problem_text):
            # skip empty lines
            if re.match(r"^\s*$", line):
                continue

            # eliminate trailing whitespaces
            aux_line = line.strip()

            # get set of words from the current line
            words = self.breakup_line(aux_line)
            for w in words:
                # word is a token
                if w in self.__tokens:
                    self.__pif.append((w, -1))
                # word is an identifier
                elif re.match("^[a-zA-Z]\w*$", w):
                    index_id = self.__symbol_table.add(w)  # index_id is a pair [hash_code, pos]
                    self.__pif.append(("ID", index_id))
                # word is a constant -- matches numbers (i.e. 34) or strings (i.e. "word")
                elif re.match("^((\d|[1-9]\d*)|(\"[^\"]*\"))$", w):
                    index_id = self.__symbol_table.add(w)
                    self.__pif.append(("CONST", index_id))
                # lexical error
                else:
                    index_error = self.__problem_text[index].find(w)
                    error = f"Lexical Error: line {index + 1} col {index_error + 1}\n"
                    sys.exit(error)
            else:
                continue
        print("Successful scanning!")
        self.write_files()

    @staticmethod
    def breakup_line(line):
        words = []
        delimiters = [',', '.', '[', ']', '{', '}', ' ', '+', '-', '*', '/', '%', '>', '<', '=', '&', '|', '!']
        pos = 0
        while pos < len(line):
            c = line[pos]
            # ignore comments in program
            if c == "/" and line[pos + 1] == "/":
                return words
            # string constant case
            if c == "\"":
                found_pos = line[pos + 1:].find("\"")
                # unclosed " error
                if found_pos == -1:
                    return words.append(line)
                else:
                    words.append(line[pos:found_pos])
                    pos = found_pos + 1
            elif c not in delimiters:
                # find closest delimiter
                min_distance = sys.maxsize
                found = False
                for d in delimiters:
                    found_pos = line[pos:].find(d)
                    if found_pos != -1:
                        min_distance = min(min_distance, found_pos)
                        found = True
                # if no delimiter is found, it means the current word is the last on the line
                if found is False:
                    return words.append(line[pos:len(line) - 1])
                words.append(line[pos:pos + min_distance])
                # print(min_distance)
                pos = pos + min_distance
            # delimiter found, skip this char
            else:
                pos += 1
        return words

    def write_files(self):
        pif_str = "PIF:\n"
        headers = ["Index", "Value"]
        pif_str += tabulate(self.__pif, headers, tablefmt="grid")
        with open("PIF.out", "w") as file:
            file.write(pif_str)

        with open("ST.out", "w") as file:
            file.write("SYMBOL_TABLE:\n" + str(self.__symbol_table))


