from random import seed, randint
from copy import deepcopy
from datetime import datetime, timedelta

def start_number():
    """
    This function generates a random number for the user to guess
    :return: the random number
    """
    seed(1)
    d1 = randint(1, 9)   # the first digit

    d2 = randint(0, 9)
    while d2 == d1:   # if the first digit is the same as the second, find another second digit
        d2 = randint(0, 9)

    # we repeat for the remaining digits
    d3 = randint(0, 9)
    while d3 == d2 or d3 == d1:
        d3 = randint(0, 9)

    d4 = randint(0, 9)
    while d4 == d3 or d4 == d2 or d4 == d1:
        d4 = randint(0, 9)

    random_number = d1 * 1000 + d2 * 100 + d3 * 10 + d4
    return random_number

def start_counter():
    now = datetime.now()
    final_time = now + timedelta(seconds=60)
    return final_time

def check_timer(final_time):
    now = datetime.now()
    if now == final_time:
        return True
    return False

def number_to_list(number):
    new_number = deepcopy(number)
    new_number = int(new_number)
    digit_list = []
    while new_number != 0:
        index = new_number % 10
        digit_list.append(index)
        new_number //= 10
    return digit_list

def number_to_frequency_list(number):
    new_number = deepcopy(number)
    digits_frequency = [0] * 10
    while new_number != 0:
        index = new_number % 10
        index = int(index)
        digits_frequency[index] += 1
        new_number //= 10
    return digits_frequency

def check_number(number):
    """
    This function returns 0 is the number is invalid, 1 otherwise
    :param number:
    :return:
    """
    if number[0] == "0":
        return 0

    if number.isdecimal() is False:
        return 0

    number = int(number)

    if number < 1000 or number > 9999:
        return 0

    digits_frequency = number_to_frequency_list(number)

    for i in range(9):
        if digits_frequency[i] > 1:
            return 0
    return 1

def codes(random_number, user_number):
    random_digits = number_to_list(random_number)
    user_digits = number_to_list(user_number)
    number_of_codes = 0

    for i in range(3):
        if random_digits[i] == user_digits[i]:
            number_of_codes += 1

    return number_of_codes

def cheat_code(user_number):
    if user_number == 8086:
        return True
    return False

def runners(random_number, user_number):
    random_frequency = number_to_frequency_list(random_number)
    user_frequency = number_to_frequency_list(user_number)
    number_of_runners = 0

    for i in range(9):
        if random_frequency[i] == user_frequency[i] and random_frequency[i] == 1:
            number_of_runners += 1

    return number_of_runners

def is_game_over(random_number, user_number):
    if user_number == False:
        return False
