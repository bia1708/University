from functions import check_number


def ui_pick_number(number_of_guesses):
    if number_of_guesses == 0:
        user_number = input("Please input your guess: ")
    else:
        user_number = input("Please try again: ")

    if check_number(user_number) == 0:
        return False
    return user_number
