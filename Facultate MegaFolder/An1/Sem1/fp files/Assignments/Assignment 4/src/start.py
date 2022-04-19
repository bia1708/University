"""
  Start the program by running this module
"""
from functions import add_expense, test_all, get_cmd_and_args, get_last_history
from ui import ui_add_expense, ui_insert_expense, ui_remove_expense, ui_list_expenses, print_commands, \
    ui_sum_of_expenses, ui_max, ui_sort_expenses, ui_filter_list, ui_undo
import traceback

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

def run_menu():
    expenses = startup_contents()
    history_list = []
    history_list.append(expenses)
    test_all()
    commands = {
        "add" : ui_add_expense,
        "insert" : ui_insert_expense,
        "remove" : ui_remove_expense,
        "list" : ui_list_expenses,
        "sum": ui_sum_of_expenses,
        "max": ui_max,
        "sort": ui_sort_expenses,
        "filter": ui_filter_list,
        "undo": ui_undo
    }
    while True:
        print("\n###############################################\nHello, Family! What would you like to do today? \n")
        print_commands(commands)
        cmd_line = input("Input your command and the arguments, or 'exit' to exit the program.\n")

        if cmd_line == "exit":
            break
        else:
            cmd, args = get_cmd_and_args(cmd_line)
            try:
                if cmd in ["add", "insert", "remove", "filter", "undo"]:
                    expenses = history_list
                else:
                    expenses = get_last_history(history_list)
                commands[cmd](expenses, *args)
            except KeyError:
                print(f"Option {cmd} is not yet implemented")
            except ValueError as ve:
                print("The following exception was thrown: ", ve)
                traceback.print_exc()
            except TypeError:
                print("Please type in the correct number of parameters!")

run_menu()