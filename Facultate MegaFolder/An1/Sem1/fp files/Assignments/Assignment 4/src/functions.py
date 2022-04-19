"""
  Program functionalities module
"""


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
    assert (check_expense_type('housekeeping')) == True
    assert (check_expense_type('food')) == True
    assert (check_expense_type('transport')) == True
    assert (check_expense_type('clothing')) == True
    assert (check_expense_type('internet')) == True
    assert (check_expense_type('others')) == True
    assert (check_expense_type('fod')) == False
    assert (check_expense_type('trasport')) == False


def check_day(day):
    """
    A function that checks if a given day is valid
    :param day: a variable of type int, the day we want to check
    :return: True or False
    """
    day = int(day)
    if day > 30 or day < 1:
        return False
    return True


def test_check_day():
    assert check_day(12) is True
    assert check_day(-1) is False
    assert check_day(0) is False
    assert check_day(40) is False
    assert check_day(1) is True
    assert check_day(30) is True


def check_validity(expense):
    """
    A function which checks the validity of an expense
    :param expense: a dictionary, representing an expense
    :return: 11 - error code for invalid expense type
             22 - error code for invalid date
             0 - the expense is valid
    """
    if check_expense_type(get_expense_type(expense)) is False:
        return 11
    if check_day(get_day(expense)) is False:
        return 22
    return 0


def check_property(symbol):
    """
    A function which checks the validity of a given property
    :param symbol: A character denoting a symbol
    :return: True or False
    """
    if symbol not in [">", "<", "="]:
        return False
    return True


def test_check_property():
    assert check_property(">") is True
    assert check_property("<") is True
    assert check_property("=") is True
    assert check_property(".") is False


def create_expense(day, expense_type, amount):
    """
    A function which creates a new expense, of type dictionary
    :param day: an int denoting the day of the expense
    :param expense_type: a string denoting the category(type) of the expense
    :param amount: an int denoting the amount of the expense
    :return: a dictionary
    """
    return {
        "day": day,
        "expense_type": expense_type,
        "amount": amount
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


def add_expense(expenses, day, expense_type, amount):
    expense = create_expense(day, expense_type, amount)
    expenses.append(expense)


def remove_day(expenses, day):
    """
    Function which removes a single day from the list
    :param expenses: a list containing the expenses
    :param day: an int representing the day we want to delete
    :return: the updated list
    """
    i = 0
    while i < len(expenses):
        if get_day(expenses[i]) == day:
            expenses.remove(expenses[i])
        else:
            i += 1
    return expenses


def remove_multiple_days(expenses, day1, day2):
    """
    Function which removes more than one day from the list
    :param expenses: a list containing the expenses
    :param day1: an int representing the day from which we want to start deleting
    :param day2: an int representing the day at which we want to stop deleting
    :return: the updated list
    """
    i = 0
    while i < len(expenses):
        if get_day(expenses[i]) >= day1 and get_day(expenses[i]) <= day2:
            expenses.remove(expenses[i])
        elif get_day(expenses[i]) > day2:
            break
        else:
            i += 1
    return expenses


def remove_type(expenses, expense_type):
    """
    Function which removes a type from the list
    :param expenses: a list containing the expenses
    :param day: a string representing the type we want to delete
    :return: the updated list
    """
    i = 0
    while i < len(expenses):
        if get_expense_type(expenses[i]) == expense_type:
            expenses.remove(expenses[i])
        else:
            i += 1


def sum_of_expenses_by_type(expenses, expense_type):
    """
    A function which calculates the sum of expenses of a given type
    :param expenses: a list containing the expenses
    :param expense_type: a string representing the type of expense we want to add to the sum
    :return: an int representing the desired sum
    """
    sum = 0
    for expense in expenses:
        if get_expense_type(expense) == expense_type:
            sum += get_amount(expense)
    return sum


def sum_of_expenses_by_day(expenses, day):
    """
    A function which calculates the sum of expenses in a given day
    :param expenses: a list containing the expenses
    :param day: an int representing the day for which we want to calculate the sum
    :return: an int representing the desired sum
    """
    sum = 0
    for expense in expenses:
        if get_day(expense) == day:
            sum += get_amount(expense)
    return sum


def test_sum_of_expenses_by_type():
    new_list = []
    add_expense(new_list, 10, "food", 50)
    add_expense(new_list, 21, "food", 40)
    add_expense(new_list, 30, "internet", 20)
    assert sum_of_expenses_by_type(new_list, "food") == 90
    assert sum_of_expenses_by_type(new_list, "internet") == 20


def max_of_expenses(expenses):
    """
    A function which determines the maximum amount spent in any day
    :param expenses: a list containing the expenses
    :return: an int, representing the desired maximum
    """
    max_amount = 0
    max_day = 0
    for i in range(1, 30):
        sum_by_day = sum_of_expenses_by_day(expenses, i)
        if sum_by_day > max_amount:
            max_amount = sum_by_day
            max_day = i
    return max_amount, max_day


def test_max_of_expenses():
    new_list = []
    add_expense(new_list, 10, "food", 20)
    add_expense(new_list, 30, "internet", 50)
    add_expense(new_list, 10, "housekeeping", 40)
    assert max_of_expenses(new_list) == (60, 10)


def sort_by_day(expenses, day):
    """
    A function which sorts the expenses in the ascending order of the amounts spent in a given day
    :param expenses: a list containing all the expenses
    :param day: an int representing the day that we want to sort
    :return: te updated list
    """
    new_list = []
    for expense in expenses:
        if day == get_day(expense):
            new_list.append(expense)
    new_list.sort(key=get_amount)
    return new_list


def test_sort_by_day():
    new_list = []
    add_expense(new_list, 10, "food", 25)
    add_expense(new_list, 10, "internet", 45)
    add_expense(new_list, 10, "others", 15)
    add_expense(new_list, 12, "food", 5)
    sorted_list = sort_by_day(new_list, 10)
    assert sorted_list == [{"day": 10, "expense_type": "others", "amount": 15}, \
                           {"day": 10, "expense_type": "food", "amount": 25}, \
                           {"day": 10, "expense_type": "internet", "amount": 45}]


def sort_by_type(expenses, expense_type):
    """
    A function which sorts the expenses in the ascending order of the amounts spent in a given category
    :param expenses: a list containing all the expenses
    :param expense_type: a string representing the type that we want to sort
    :return: te updated list
    """
    new_list = []
    for expense in expenses:
        if expense_type == get_expense_type(expense):
            new_list.append(expense)
    new_list.sort(key=get_amount)
    return new_list


def test_sort_by_type():
    new_list = []
    add_expense(new_list, 12, "food", 25)
    add_expense(new_list, 30, "food", 45)
    add_expense(new_list, 10, "others", 15)
    add_expense(new_list, 12, "food", 5)
    sorted_list = sort_by_type(new_list, "food")
    assert sorted_list == [{"day": 12, "expense_type": "food", "amount": 5}, \
                           {"day": 12, "expense_type": "food", "amount": 25}, \
                           {"day": 30, "expense_type": "food", "amount": 45}]


def filter_without_params(expenses, filter):
    """
    A function which only keeps the expenses of a certain type from a list
    :param expenses: the list we want to filter
    :param filter: a str representing the category we want to keep
    :return: a new list containing only the required category
    """
    new_list = []
    for expense in expenses:
        if get_expense_type(expense) == filter:
            new_list.append(expense)
    return new_list

def test_filter_without_params():
    new_list = []
    add_expense(new_list, 12, "food", 25)
    add_expense(new_list, 30, "food", 45)
    add_expense(new_list, 10, "others", 15)
    add_expense(new_list, 12, "food", 5)
    filtered_list = filter_without_params(new_list, "food")
    assert filtered_list == [{"day": 12, "expense_type": "food", "amount": 25}, \
                           {"day": 30, "expense_type": "food", "amount": 45}, \
                           {"day": 12, "expense_type": "food", "amount": 5}]

def get_last_history(history_list):
    return history_list[-1]


def filter_with_params(expenses, filter, operator, amount):
    """
    A function which only keeps the expenses of a certain type and certain amount from a list
    :param expenses: the list we want to filter
    :param filter: a str representing the category we want to keep
    :param operator: a char, one of the following symbols: '<', '>', '='
    :param amount: an int representing the desired amount we want as a filter
    :return: a new list containing only the required category
    """
    new_list = []
    amount = int(amount)
    for expense in expenses:
        if get_expense_type(expense) == filter:
            if operator == "<" and get_amount(expense) < amount:
                new_list.append(expense)
            elif operator == ">" and get_amount(expense) > amount:
                new_list.append(expense)
            elif operator == "=" and get_amount(expense) == amount:
                new_list.append(expense)
    return new_list

def test_filter_with_params():
    new_list = []
    add_expense(new_list, 12, "food", 25)
    add_expense(new_list, 30, "food", 45)
    add_expense(new_list, 10, "others", 15)
    add_expense(new_list, 12, "food", 5)
    filtered_list = filter_with_params(new_list, "food", ">", 20)
    assert filtered_list == [{"day": 12, "expense_type": "food", "amount": 25}, \
                             {"day": 30, "expense_type": "food", "amount": 45}]

def test_all():
    test_check_expense_type()
    test_check_day()
    test_create_expense()
    test_get_cmd_and_args()
    test_check_property()
    test_sum_of_expenses_by_type()
    test_max_of_expenses()
    test_sort_by_day()
    test_sort_by_type()
    test_filter_without_params()
    test_filter_with_params()
