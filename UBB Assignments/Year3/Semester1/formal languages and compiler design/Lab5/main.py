from Scanner import Scanner
from grammar import Grammar
from parser import Parser


def main():
    grammar = Grammar()
    assert grammar.cfg_check(), "Cfg check is not correct!"
    scanner = Scanner(problem="p3.txt")
    parser = Parser(grammar=grammar, scanner=scanner, out_file='output.txt')
    parser.run()
    # grammar.print_terminals()
    # grammar.print_non_terminals()
    # grammar.print_productions()
    # grammar.print_productions_for_non_terminal("program")
    # print("CFG Check:", grammar.cfg_check())


if __name__ == "__main__":
    main()
