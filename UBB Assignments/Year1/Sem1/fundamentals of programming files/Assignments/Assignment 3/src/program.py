#Problem 3 - Family expenses

"""
  Write non-UI functions below
"""
from datetime import datetime
import traceback

def check_expense_type(expense_type):
    """
    A function which checks if the expense type given as a parameter exists
    :param expense_type: a string containing the expense type that we want to use
    :return: True or False
    """
    categories = ['housekeeping', 'food', 'transport', 'clothing', 'internet', 'others']
    for categ in categories:
        if categ == expense_type:
            return True
    return False

def test_check_expense_type():
    assert(check_expense_type('housekeeping')) == True
    assert(check_expense_type('food')) == True
    assert(check_expense_type('transport')) == True
    assert(check_expense_type('clothing')) == True
    assert(check_expense_type('internet')) == True
    assert(check_expense_type('others')) == True
    assert(check_expense_type('fod')) == False
    assert(check_expense_type('trasport')) == False

def check_day(day):
    """
    A function that checks if a given day is valid
    :param day: a variable of type int, the day we want to check
    :return: True or False
    """

    if day > 30 or day < 1:
        return False
    return True

def test_check_day():
    assert check_day(12) == True
    assert  check_day(-1) == False
    assert check_day(0) == False
    assert check_day(40) == False
    assert check_day(1) == True
    assert check_day(30) == True

def check_property(property):
    """
    A function which checks the validity of a given property
    :param property: A character denoting a symbol
    :return: True or False
    """
    if property not in [">", "<", "="]:
        return False
    return True

def test_check_property():
    assert check_property(">") == True
    assert check_property("<") == True
    assert check_property("=") == True
    assert check_property(".") == False

def create_expense(day, expense_type, amount):
    """
    A function which creates a new expense, of type dictionary
    :param day: an int denoting the day of the expense
    :param expense_type: a string denoting the category(type) of the expense
    :param amount: an int denoting the amount of the expense
    :return: a dictionary
    """
    return {
        "day" : day,
        "expense_type" : expense_type,
        "amount" : amount
    }

def test_create_expense():
    assert create_expense(10, 'housekeeping', 150) == {"day": 10, "expense_type": "housekeeping", "amount": 150}
    assert create_expense(30, 'food', 100) == {"day": 30, "expense_type": "food", "amount": 100}

def get_cmd_and_args(cmd_line):
    """
    A function which separates the command and the arguments from the user's input
    :param cmd_line: a string, the user's input with the command and the args
    :return: a string for the command name and a list for the arguments
    """
    position = cmd_line.find(" ")
    if position == -1:
        return cmd_line, []
    cmd_name = cmd_line[:position]
    args = cmd_line[position:].split()
    args = [arg.strip() for arg in args]
    return cmd_name, args

def test_get_cmd_and_args():
    assert get_cmd_and_args("add food 5") == ("add", ["food", "5"])
    assert get_cmd_and_args("insert 10 food 5") == ("insert", ["10", "food", "5"])
    assert get_cmd_and_args("remove food") == ("remove", ["food"])
    assert get_cmd_and_args("list internet > 10") == ("list", ["internet", ">", "10"])

def get_day(expense):
    return expense["day"]

def get_expense_type(expense):
    return expense["expense_type"]

def get_amount(expense):
    return expense["amount"]

def set_day(expense, day):
    expense["day"] = day

def set_expense_type(expense, expense_type):
    expense["expense_type"] = expense_type

def set_amount(expense, amount):
    expense["amount"] = amount

def startup_contents():
    """
    A function which provides the startup contents of the expenses list
    :return: a list containing all the expenses
    """
    expenses = []
    add_expense(expenses, 1, "food", 10)
    add_expense(expenses, 2, "food", 15)
    add_expense(expenses, 3, "food", 5)
    add_expense(expenses, 4, "food", 10)
    add_expense(expenses, 5, "food", 10)
    add_expense(expenses, 6, "housekeeping", 10)
    add_expense(expenses, 7, "housekeeping", 10)
    add_expense(expenses, 8, "internet", 10)
    add_expense(expenses, 9, "transport", 10)
    add_expense(expenses, 10, "others", 10)
    return expenses

def test_all():
    test_check_expense_type()
    test_check_day()
    test_create_expense()
    test_get_cmd_and_args()
    test_check_property()

##################FUNCTIONALITIES########################

def add_expense(expenses, day, expense_type, amount):
    expense = create_expense(day, expense_type, amount)
    expenses.append(expense)


"""
  Write the command-driven UI below
"""

def ui_add_expense(expenses, expense_type, amount):
    if check_expense_type(expense_type) == False:
        print("The category you typed in doesn't exist! Please try again.")
    else:
        current_date = datetime.today()
        day = current_date.strftime("%d")
        add_expense(expenses, int(day), expense_type, int(amount))

def ui_insert_expense(expenses, day, expense_type, amount):
    if check_day(int(day)) == False:
        print("Please enter a valid date!")
    elif check_expense_type(expense_type) == False:
        print("The category you typed in doesn't exist! Please try again.")
    else:
        add_expense(expenses, int(day), expense_type, int(amount))
        expenses.sort(key = get_day)

def remove_expense(expenses, *args):
    if args[0].isdigit() == True:
        day1 = int(args[0])
        if len(args) == 1:
            i = 0
            while i < len(expenses):
                if get_day(expenses[i]) == day1:
                    expenses.remove(expenses[i])
                else:
                    i += 1
        elif args[2].isdigit() == True:
            day2 = int(args[2])
            i = 0
            while i < len(expenses):
                if get_day(expenses[i]) >= day1 and get_day(expenses[i]) <= day2:
                    expenses.remove(expenses[i])
                elif get_day(expenses[i]) > int(args[2]):
                    break
                else:
                    i += 1
    else:
        i = 0
        if check_expense_type(args[0]) == False:
            print("The category you typed in doesn't exist! Please try again.")
        else:
            while i < len(expenses):
                if get_expense_type(expenses[i]) == args[0]:
                    expenses.remove(expenses[i])
                else:
                    i += 1

def display_expense(expense):
    print("Day: " + str(get_day(expense)) +
          " ||  Type: " + str(get_expense_type(expense)) +
          " ||  Sum: " + str(get_amount(expense)))

def list_expenses(expenses, type = None, property = None, amount = 0):
    check_display = False
    if type == None:
        for expense in expenses:
            display_expense(expense)
            check_display = True
    elif property is None:
        for expense in expenses:
            if type == get_expense_type(expense):
                display_expense(expense)
                check_display = True
    elif check_property(property) == False:
        print("Please enter a valid symbol!")
        check_display = True
    elif property == "<":
        for expense in expenses:
            if type == get_expense_type(expense) and get_amount(expense) < int(amount):
                display_expense(expense)
                check_display = True
    elif property == "=":
        for expense in expenses:
            if type == get_expense_type(expense) and get_amount(expense) == int(amount):
                display_expense(expense)
                check_display = True
    else:
        for expense in expenses:
            if type == get_expense_type(expense) and get_amount(expense) > int(amount):
                display_expense(expense)
                check_display = True
    if check_display == False:
        print("Looks like there aren't any expenses here!")

def print_commands(commands):
    print("You can only choose one of these commands:")
    for key in commands:
        print(key)
    print("\nThe categories you can choose from are: 'housekeeping', 'food',",
          " 'transport', 'clothing', 'internet', 'others'")

def run_menu():
    expenses = startup_contents()

    commands = {
        "add" : ui_add_expense,
        "insert" : ui_insert_expense,
        "remove" : remove_expense,
        "list" : list_expenses
    }
    while True:
        print("\nHello, Family! What would you like to do today? \n")
        print_commands(commands)
        cmd_line = input("Input your command and the arguments, or 'exit' to exit the program.\n")

        if cmd_line == "exit":
            break
        else:
            cmd, args = get_cmd_and_args(cmd_line)
            try:
                commands[cmd](expenses, *args)
            except KeyError:
                print(f"Option {cmd} is not yet implemented")
            except ValueError as ve:
                print("The following exception was thrown: ", ve)
                traceback.print_exc()


test_all()

run_menu()

