from enum import Enum
from Scanner import Scanner
from grammar import Grammar


class Parser:
    class State(Enum):
        DONE = 0
        ERROR = 1
        CONTINUE = 2
        BACKTRACK = 3

    def __init__(self, grammar: Grammar, scanner: Scanner, out_file):
        self.grammar = grammar
        self.out_file = out_file
        self.scanner = scanner
        self.backlist = []
        self.index = 0
        self.sequence = self.scanner.get_pif()
        self.input = [self.grammar.get_start_symbol()]
        self.state = Parser.State.CONTINUE

    def log_step(self, step):
        msg = f"<=={step}==>\n({self.state}, {self.index}, {self.backlist}, {self.input})\n\n"
        with open(self.out_file, "a") as f:
            f.write(msg)

        print(msg)

    def expand(self):
        self.log_step("EXPAND")
        non_terminal = self.input.pop(0)
        self.backlist.append((non_terminal, 0))
        new_production = self.grammar.get_productions_for_non_terminal(non_terminal)[0]
        self.input = new_production + self.input

    def advance(self):
        self.log_step("ADVANCE")
        self.backlist.append(self.input.pop(0))
        self.index += 1

    def momentary_insuccess(self):
        self.log_step("MOMENTARY_INSUCCESS")
        self.state = Parser.State.BACKTRACK

    def back(self):
        self.log_step("BACK")
        item = self.backlist.pop()
        self.input.insert(0, item)
        self.index -= 1

    def success(self):
        self.log_step("SUCCESS")
        self.state = Parser.State.DONE

    def another_try(self):
        self.log_step("ANOTHER TRY")

        if self.backlist:
            last_nt = self.backlist.pop()
            nt, production_nr = last_nt

            productions = self.grammar.get_productions_for_non_terminal(nt)

            if production_nr + 1 < len(productions):
                self.state = Parser.State.CONTINUE

                new_tuple = (nt, production_nr + 1)
                self.backlist.append(new_tuple)

                len_last_production = len(productions[production_nr])
                self.input = self.input[len_last_production:]
                new_production = productions[production_nr + 1]
                self.input = new_production + self.input
            else:
                len_last_production = len(productions[production_nr])
                self.input = self.input[len_last_production:]
                if not len(self.input) == 0:
                    self.input = [nt] + self.input
        else:
            self.state = Parser.State.ERROR

    def error(self):
        self.log_step("ERROR")
        self.state = Parser.State.ERROR

    def run(self):
        while (self.state != Parser.State.DONE) and (self.state != Parser.State.ERROR):
            if self.state == Parser.State.CONTINUE:
                # Check end of run
                if len(self.input) == 0 and self.index == len(self.sequence):
                    self.success()
                # If current node is a non-terminal, expand it
                elif self.input[0] in self.grammar.get_non_terminals():
                    self.expand()
                elif self.index < len(self.sequence) and self.input[0] == self.sequence[self.index][0]:
                    self.advance()
                else:
                    # change state to Parser.State.BACKTRACK and go to the other set of rules
                    self.momentary_insuccess()
            elif self.state == Parser.State.BACKTRACK:
                # If there are no more productions to check and we can backtrack, try another node
                if self.backlist and self.backlist[-1] in self.grammar.get_terminals():
                    self.back()
                else:
                    self.another_try()

        if self.state == Parser.State.ERROR:
            self.error()
