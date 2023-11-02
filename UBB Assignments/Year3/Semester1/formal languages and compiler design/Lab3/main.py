from Scanner import Scanner

problems = ["p1.txt", "p2.txt", "p3.txt", "p1err.txt"]

if __name__ == "__main__":
    while True:
        print("Available problems: p1.txt, p2.txt, p3.txt, p1err.txt\nPress x to exit.\n")
        problem_number = input("Problem number:")
        if problem_number == 'x':
            exit(0)
        Scanner(problems[int(problem_number)])
