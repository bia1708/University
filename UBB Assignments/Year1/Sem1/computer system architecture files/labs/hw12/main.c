// Read from the console a list of numbers in base 10. Write to the console only the prime numbers.

#include <stdio.h>

int check_prime(int);

int main()
{
    printf("Please enter a set of numbers, ending in a 0: ");
    int n;
    scanf("%d", &n);
    
    while(n != 0){
        if (check_prime(n) == 1)
            printf("%d ", n);
        scanf("%d", &n);
    }
   
    return 0;
}

// cd C:\Users\PC\Documents\CSA\hw12
// nasm check_prime.asm -fwin32 -o check_prime.obj
// cl main.c /link check_prime.obj