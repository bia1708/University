"""
Implement the solution here. 
You may add other source files.
Make sure you commit & push the source code before the end of the test.

Solutions using user-defined classes will not be graded.
"""
from functions import start_number, start_counter, check_timer, codes, runners, cheat_code
from ui import ui_pick_number

def run_game():
    print("Hello and welcome to the CodeRunner game!")

    random_number = start_number()
    number_of_guesses = 0
    user_number = ui_pick_number(number_of_guesses)
    date = start_counter()
    number_of_guesses += 1

    while True:
        if check_timer(date) is True:
            print("GAME OVER")
            break
        elif user_number is False:
            print("GAME OVER")
            break
        elif int(user_number) == int(random_number):
            print(f"You won in {number_of_guesses} tries!")
        elif cheat_code(int(user_number)) is True:
            print("You found the random number! By accident, I guess... It was: ", random_number)
            break
        else:
            user_number = int(user_number)
            random_number = int(random_number)
            number_of_codes = codes(random_number, user_number)
            number_of_runners = runners(random_number, user_number)
            print(f"You were close! Codes: {number_of_codes}. Runners: {number_of_runners}.")
            user_number = ui_pick_number(number_of_guesses)
            date = start_counter()

run_game()
