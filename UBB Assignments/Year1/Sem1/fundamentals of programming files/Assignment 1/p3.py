# Solve the problem from the third set here

# Problem 12
# Determine the age of a person, in number of days.
# Take into account leap years, as well as the date
# of birth and current date (year, month, day).
# Do not use Python's inbuilt date/time functions.

def get_birthday():
    # function which reads the user's birthday
    # and creates a list containing the day,
    # month and year

    bday = []

    print("Hi! Please type in your birthday!")

    bday.append(int(input("Day: ")))
    bday.append(int(input("Month: ")))
    bday.append(int(input("Year: ")))

    return bday

def get_today():
    # function which reads the current date
    # and creates a list containing the day,
    # month and year

    today = []

    print("Now please type in the current date: ")

    today.append(int(input("Day: ")))
    today.append(int(input("Month: ")))
    today.append(int(input("Year: ")))

    return today

def is_leap_year(x):
    # function which determines whether a given
    # year is a leap year
    # input: x - a natural number, the given year
    # output: True, if the year is a leap year,
    #         False otherwise

    if x % 4 == 0:
        if x % 100 == 0 and x % 400:
            return False
        else:
            return True
    return False

def total_number_of_days(date):
    # function which calculates the total
    # number of days since 1/01/1
    # input: date - an array containing a
    #        date
    # output: days - a natural number

    days = 0
    months = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    for i in range(date[2]):
        if is_leap_year(i):
            days += 366
        else:
            days += 365

    for i in range(date[1]):
        days += months[i]

    if is_leap_year(date[2]):
        days += 1

    days += date[0]

    return days

def get_age_in_days():
    # function which returns the user's age
    # in days
    # output: age - a natural number, the user's
    #         age in days

    bday = get_birthday()
    today = get_today()
    days_today = total_number_of_days(today)
    days_bday = total_number_of_days(bday)

    # we calculate the age by subtracting the
    # number of days until the user's birthday
    # from the number of days until today
    age = days_today - days_bday
    return age

def show_age():
    # function which displays the user's age
    # output : the user's age in days

    age = get_age_in_days()
    print("This is your age in days: " + str(age))

show_age()
