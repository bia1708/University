#3 and 9
# Write the implementation for A2 in this file
#

# UI section
# (write all functions that have input or print statements here). 
# Ideally, this section should not contain any calculations relevant to program functionalities

from math import sqrt


def print_menu():
    # This function displays the menu of the program
    print("Hello! What would you like to do?")
    print("1. Add some numbers to the list. \n"
          "2. Display all the existing numbers in the list. \n"
          "3. Display the longest sequence of numbers having the same modulus. \n"
          "4. Display the longest sequence of consecutive number pairs which have equal sum. \n"
          "5. Press x to exit the application.")

"""
def add_number(numbers):
    # This function allows the user to add a list of complex numbers to the list
    # input: numbers - a list containing complex numbers, each one represented through a list

    print("Press the x key when you want to stop adding numbers.")

    while True:
        try:
            a = int(input("a = "))
            b = int(input("b = "))
            numbers.append([a, b])
        except ValueError as ve:
            print("You have to insert a number!", ve)

        key = input()
        if key == 'x':
            break
"""

def ui_add_number(numbers):
    try:
        real = int(input("a = "))
        imag = int(input("b = "))
        add_number(numbers, real, imag)
    except ValueError as ve:
        print("You have to insert a number!", ve)

    # key = input()
    # if key == 'x':
    #     break

def display_numbers(numbers, pos = 0, length = None):
    # This function displays some(if not all) numbers in the list.
    if length == 0:
        print("There aren't any numbers with this property in the list.")
    else:
        print("\n These are the numbers you're looking for:")
        if length is None:
            length = len(numbers)
        for i in range(pos, pos + length):
            if get_imag(numbers[i]) == 0:
                print("z" + str(i + 1) + " = " + str(get_real(numbers[i])) + "\n")
            elif get_real(numbers[i]) == 0:
                print("z" + str(i + 1) + " = " + str(get_imag(numbers[i])) + "i \n")
            else:
                print("z" + str(i + 1) + " = " + str(get_real(numbers[i])) + " + " + str(get_imag(numbers[i])) + "i \n")

def run_menu():
    # This is a list of numbers provided at startup:
    numbers = [create_complex(3, 4), create_complex(4, 3), create_complex(1, -7), create_complex(1, 1),
               create_complex(1, -7), create_complex(1, 7), create_complex(1, -7), create_complex(1, 3),
               create_complex(1, -1), create_complex(1, 3), create_complex(1, -1)]

    options = {
        1: ui_add_number,
        2: display_numbers,
        3: display_numbers,
        4: display_numbers
    }

    while True:
        print_menu()
        opt = input("Choose an option: ")
        try:
            if opt == 'x':
                break
            elif opt == '3':
                params = longest_set(check_modules, numbers, 1)
                options[int(opt)](numbers, params[0], params[1])
            elif opt == '4':
                params = longest_set(check_sum, numbers, 2)
                options[int(opt)](numbers, params[0], params[1])
            else: options[int(opt)](numbers)
        except ValueError as ve:
            print("Please select one of the existing options! \n", ve, "\n")
        except KeyError:
            print(f"We haven't implemented {opt} yet! \n")

#############################################
# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values

# print('Hello A2'!) -> prints aren't allowed here!

def create_complex(real, imag):
    return {
        'real':real,
        'imag':imag
    }

def add_number(numbers, real, imag):
     complex = create_complex(real, imag)
     numbers.append(complex)

def get_real(complex):
    return complex["real"]

def get_imag(complex):
    return complex["imag"]

def set_real(complex):
    complex["real"] = real

def set_imag(complex):
    complex["imag"] = imag

def calculate_modulus(real, imag):
    # This function calculates the modulus of a complex number
    # input: a, b - natural numbers, the real and the imaginary part of z
    # output: the modulus of the complex number z

    return round(sqrt(real * real + imag * imag), 2)

def test_modulus():
    # Test function for calculate_modulus()

    assert calculate_modulus(3, 4) == 5
    assert calculate_modulus(1, 1) == 1.41
    assert calculate_modulus(0, 0) == 0

test_modulus()

"""
def create_modulus_list(numbers, modules):
    # This is a function which creates a list containing all the modules of the complex numbers
    for i in range(len(numbers)):
        a = get_a(numbers, i)
        b = get_b(numbers, i)
        modules.append(calculate_modulus(a, b))



def longest_modulus_seq(numbers):
    # Function which finds the longest sequence of numbers of a given property
    modules = []
    create_modulus_list(numbers, modules)
    pos = 0
    max_length = 0
    for i in range(len(modules) - 1):
        if modules[i] == modules[i + 1]:
            len = 1
            for j in range(i + 1, len(modules) - 1):
                if modules[j] == modules[j + 1]:
                    len += 1
            if len > max_length:
                pos = i
                max_length = len
            i += len
    show_sequence(numbers, pos, max_length)
    # TODO: implement show_sequence
"""

def check_modules(numbers, pos):
    # This function checks the modulus property for two consecutive numbers in the 'numbers' list
    # input : numbers - the numbers list
    #         pos - the position in the list where we want to test this
    # output : True if the numbers have the property, False otherwise


    mod_z1 = calculate_modulus(get_real(numbers[pos]), get_imag(numbers[pos]))
    mod_z2 = calculate_modulus(get_real(numbers[pos + 1]), get_imag(numbers[pos + 1]))

    if mod_z1 == mod_z2:
        return True
    return False

def check_sum(numbers, pos):
    # This function checks the sum property of three consecutive numbers in the 'numbers' list
    # input : numbers - the numbers list
    #         pos - the position in the list where we want to test this
    # output : True if the numbers have the property, False otherwise

    sum1_real = get_real(numbers[pos]) + get_real(numbers[pos + 1])
    sum1_imag = get_imag(numbers[pos]) + get_imag(numbers[pos + 1])
    sum2_real = get_real(numbers[pos + 1]) + get_real(numbers[pos + 2])
    sum2_imag = get_imag(numbers[pos + 1]) + get_imag(numbers[pos + 2])

    if sum1_real == sum2_real and sum1_imag == sum2_imag:
        return True
    return False

def longest_set(property, numbers, index):
    # This function finds the longest possible sequence of numbers with a given property in the 'numbers' list
    pos = 0
    max_length = 0
    length = 0
    for i in range(len(numbers) - index):
        if property(numbers, i) == True:
            length = index + 1
            j = i + 1
            while j < len(numbers) - index and property(numbers, j) is not False:
                length += 1
                j += 1

            """
            for j in range(i + 1, len(numbers) - 1):
                if property(numbers, j) == True or property(numbers, j) == 'overflow':
                    length += 1
                    print("yay")
                else:
                    break
            """
            if length > max_length:
                pos = i
                max_length = length
            i += length
    return pos, max_length

run_menu()

