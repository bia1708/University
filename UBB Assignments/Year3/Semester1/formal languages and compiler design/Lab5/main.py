from grammar import Grammar


def main():
    grammar = Grammar()
    grammar.print_terminals()
    grammar.print_non_terminals()
    # grammar.print_productions()
    grammar.print_productions_for_non_terminal("condition")
    print("CFG Check:", grammar.cfg_check())


if __name__ == "__main__":
    main()
