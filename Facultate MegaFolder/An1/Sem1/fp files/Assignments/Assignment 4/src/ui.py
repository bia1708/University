"""
  User interface module
"""
from functions import get_day, get_amount, get_expense_type, check_validity, create_expense, add_expense, \
    check_property, check_expense_type, sum_of_expenses_by_type, check_day, max_of_expenses, sort_by_day, sort_by_type, \
    filter_without_params, get_last_history, filter_with_params, remove_day, remove_type, remove_multiple_days
from datetime import datetime


# ~~~~~~~~~~~~PRINTS~~~~~~~~~~~~~

def print_commands(commands):
    print("You can only choose one of these commands:")
    for key in commands:
        print(key)
    print("\nThe categories you can choose from are: 'housekeeping', 'food',",
          " 'transport', 'clothing', 'internet', 'others'")


def display_expense(expense):
    print("Day: " + str(get_day(expense)) +
          " ||  Type: " + str(get_expense_type(expense)) +
          " ||  Sum: " + str(get_amount(expense)))


def display_list(list):
    for element in list:
        display_expense(element)


# ~~~~~~~~~~~UI FUNCTIONS~~~~~~~~~~~

def ui_add_expense(history_list, expense_type, amount):
    current_date = datetime.today()
    day = current_date.strftime("%d")
    if check_validity(create_expense(day, expense_type, amount)) == 11:  # error code for invalid type
        print("The category you typed in doesn't exist! Please try again.")
    else:
        new_list = get_last_history(history_list).copy()
        history_list.append(new_list)
        add_expense(new_list, int(day), expense_type, int(amount))


def ui_insert_expense(history_list, day, expense_type, amount):
    if check_validity(create_expense(day, expense_type, amount)) == 22:  # error code for invalid date
        print("Please enter a valid date!")
    elif check_validity(create_expense(day, expense_type, amount)) == 11:  # error code for invalid type
        print("The category you typed in doesn't exist! Please try again.")
    else:
        new_list = get_last_history(history_list).copy()
        history_list.append(new_list)
        add_expense(new_list, int(day), expense_type, int(amount))
        new_list.sort(key=get_day)


def ui_remove_expense(history_list, *args):
    if args[0].isdigit() is True:
        day1 = int(args[0])
        if len(args) == 1:
            new_list = get_last_history(history_list).copy()
            history_list.append(new_list)
            remove_day(new_list, day1)
        elif args[2].isdigit() is True:
            day2 = int(args[2])
            new_list = get_last_history(history_list).copy()
            history_list.append(new_list)
            remove_multiple_days(new_list, day1, day2)
    else:
        type = args[0]
        if check_expense_type(type) is False:
            print("The category you typed in doesn't exist! Please try again.")
        else:
            new_list = get_last_history(history_list).copy()
            history_list.append(new_list)
            remove_type(new_list, type)


def ui_list_expenses(expenses, expense_type=None, symbol=None, amount=0):
    check_display = False
    if expense_type is None:
        for expense in expenses:
            display_expense(expense)
            check_display = True
    elif symbol is None:
        for expense in expenses:
            if expense_type == get_expense_type(expense):
                display_expense(expense)
                check_display = True
    elif check_property(symbol) is False:
        print("Please enter a valid symbol!")
        check_display = True
    elif symbol == "<":
        for expense in expenses:
            if expense_type == get_expense_type(expense) and get_amount(expense) < int(amount):
                display_expense(expense)
                check_display = True
    elif symbol == "=":
        for expense in expenses:
            if expense_type == get_expense_type(expense) and get_amount(expense) == int(amount):
                display_expense(expense)
                check_display = True
    else:
        for expense in expenses:
            if expense_type == get_expense_type(expense) and get_amount(expense) > int(amount):
                display_expense(expense)
                check_display = True
    if check_display is False:
        print("Looks like there aren't any expenses here!")


def ui_sum_of_expenses(expenses, expense_type):
    if check_expense_type(expense_type) is True:
        sum_of_expenses = sum_of_expenses_by_type(expenses, expense_type)
        print(f"You have spent a total of {sum_of_expenses} ron in the {expense_type} category.")
    else:
        print("Please enter a valid category!")


def ui_max(expenses):
    max_amount, max_day = max_of_expenses(expenses)
    print(f"The maximum amount was spent on day {max_day} and it is {max_amount} ron.")


def ui_sort_expenses(expenses, sorting_property):
    if sorting_property.isdigit():
        day = int(sorting_property)
        if check_day(day) is False:
            print("Please type in a valid day!")
        else:
            new_list = sort_by_day(expenses, day)
            display_list(new_list)
    else:
        type = sorting_property
        if check_expense_type(type) is False:
            print("Please enter a valid category!")
        else:
            new_list = sort_by_type(expenses, type)
            display_list(new_list)


def ui_filter_list(history_list, *args):
    filter = args[0]
    if check_expense_type(filter) is False:
        print("Please enter a valid category!")
    else:
        if len(args) == 1:
            history_list.append(filter_without_params(get_last_history(history_list), filter))
        else:
            operator = args[1]
            amount = args[2]
            if check_property(operator) is False:
                print("Please enter a valid symbol!")
            elif amount.isdigit() is False:
                print("Please enter a valid amount!")
            else:
                history_list.append(filter_with_params(get_last_history(history_list), filter, operator, amount))


def ui_undo(history_list):
    if len(history_list) > 1:
        history_list.pop()
    else:
        print("You can't do this operation anymore!")
