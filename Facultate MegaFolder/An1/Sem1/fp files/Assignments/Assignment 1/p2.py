# Solve the problem from the second set here

# Problem 10
# The palindrome of a number is the number obtained by reversing the
# order of its digits (e.g. the palindrome of 237 is 732). For a given
# natural number n, determine its palindrome.

def palindrome_of_n(n):
    # function that creates the palindrome of
    # a given number n
    # input: n - a natural number
    # output: pal - a natural number, the palindrome
    #         of n

    pal = 0

    while n != 0:
        pal = pal * 10 + n % 10
        n //= 10

    return pal

def get_n() :
    # function that takes the user's input for n
    # output : n - the number whose palindrome we want

    n = int(input("Choose a natural number n: "))

    return n

def show_palindrome() :
    # function which displays the palindrome of a given
    # number n
    # output : the palindrome of the given number n

    n = get_n()
    pal = palindrome_of_n(n)

    print("The palindrome of n is : " + str(pal))

show_palindrome()

