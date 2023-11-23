from FiniteAutomaton import FiniteAutomaton
from Scanner import Scanner

problems = ["p1.txt", "p2.txt", "p3.txt", "p1err.txt"]

if __name__ == "__main__":
    while True:
        print("Available problems: p1.txt (0), p2.txt(1), p3.txt(2), p1err.txt(3), finite automata(4)\nPress x to exit.\n")
        problem_number = input("Problem number:")
        if problem_number == 'x':
            exit(0)
        elif problem_number == '4':
            # Load the Finite Automaton
            fa = FiniteAutomaton()
            fa_filename = input("Enter the filename containing FA elements: ")
            fa.read_from_file(fa_filename)

            # Display FA elements
            fa.display_elements()
        else:
            Scanner(problems[int(problem_number)])
