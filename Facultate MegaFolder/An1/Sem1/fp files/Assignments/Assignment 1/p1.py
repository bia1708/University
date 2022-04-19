# Solve the problem from the first set here

# Problem 5
# Generate the largest prime number smaller
# than a given natural number n. If such a number does not exist, a message should be displayed.

from math import sqrt

def is_prime(x) :
    # function which determines whether or not a given
    # number x is prime
    # input : x - a natural number
    # output : returns True if the number is prime
    #          otherwise, it returns False

    if x == 2 :
        return True
    if x % 2 == 0 :
        return False
    for d in range(3, int(sqrt(x)) + 1, 2) :
        if x % d == 0 :
            return False
    return True

def get_n():
    # function that takes the user's input for n
    # output : n - the number whose palindrome we want

    n = int(input("Choose n: "))

    return n

def show_biggest_prime() :
    # function which prints the biggest prime number
    # smaller that n, or another message if there is
    # no such number
    # output : the number we were looking for or an
    #          error message

    n = get_n()

    if n <= 2 :
        print("There isn't a smaller prime number!!!")
    else:
        n -= 1
        while is_prime(n) == False :
            n -= 1

    print("The number you are looking for is: " + str(n))

show_biggest_prime()