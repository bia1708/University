/*
 Write 2 c programs, A and B. A will create 2 prcesses p1 and p2. p1 will
have provided (by any means (necessary)) a file containing random text
then it will read from the standard input (keyboard) a number (n).
p1 will send the nth character from the file to p2 via pipe.
p2 will write on the standard output (the console) the nature of that
character (letter, digit, other) and will send it to B via fifo.
B will display on the standard output the ascii code of that character.
The source file must be compiled using gcc with -Wall -g options WITHOUT WARNINGS OR SYNTAX ERRORS!!!
Memory leacks and zombie processes are not allowed.
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
        if(mkfifo("./fifo", 0600) < 0){
                perror("no fifo");
                exit(1);
        }
        int p[2];
        pipe(p);
        int f1 = fork();
        if(f1 == -1){
                perror("no fork");
                exit(1);
        } else if(f1 == 0) {
                close(p[0]);
                FILE* f = fopen(argv[1], "r");
                int n;
                printf("NR: ");
                scanf(" %d", &n);
                char c;
                int i;
                for(i = 0; i < n; i++)
                        fscanf(f, "%c", &c);
                write(p[1], &c, sizeof(char));
                fclose(f);
                close(p[1]);
                exit(0);
        }


        int f2 = fork();
        if(f2 == -1){
                perror("no fork 2");
                exit(1);
        } else if(f2 == 0) {
                close(p[1]);
                char c;
                read(p[0], &c, sizeof(char));
                if((c >= 'a' && c <= 'z') ||( c >= 'A' && c <= 'Z'))
                        printf("letter");
                else if(c >= '0' && c <= '9')
                        printf("number");
                else printf("other");
                int wr_fifo = open("./fifo", O_WRONLY);
                write(wr_fifo, &c, sizeof(char));
                close(wr_fifo);
                close(p[0]);
                exit(0);
        }

        close(p[0]);
        close(p[1]);

        wait(0);

        wait(0);

        return 0;
}
