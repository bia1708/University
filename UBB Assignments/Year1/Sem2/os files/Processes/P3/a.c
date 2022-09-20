/*
 Write 2 c programs, A and B. A will create 2 prcesses p1 and p2. p1 will
have provided (by any means (necessary)) a file containing only numbers (as
many as you like) then it will read from the standard input (keyboard)
a number (n). p1 will send the first n numbers from the file to p2 via pipe.
p2 will send the sum of al the odd numbers received to B, via fifo.
B will display on the standard output (the console) the number received.
The source file must be compiled using gcc with -Wall -g options WITHOUT WARNINGS OR SYNTAX ERRORS!!!
Memory leacks and zombie processes are not allowed.
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
        if(mkfifo("./fifo", 0600) < 0){
                perror("No fifo?");
                exit(1);
        }
        int p[2];
        pipe(p);
        int f = fork();
        if(f == -1){
                perror("No fork?");
                exit(1);
        } else if(f == 0){
                close(p[0]);
                FILE* file = fopen(argv[1], "r");
                int n;
                printf("numar?");
                scanf("%d", &n);
                int i;
                write(p[1], &n, sizeof(int));
                for(i = 0; i < n; i++){
                        int read_nr;
                        fscanf(file, "%d",  &read_nr);
                        write(p[1], &read_nr, sizeof(int));
                }
                fclose(file);
                close(p[1]);
                exit(1);
        } else {
                close(p[1]);
                int i, sum = 0, n;
                read(p[0], &n, sizeof(int));
                for(i = 0; i < n; i++){
                        int nr;
                        read(p[0], &nr, sizeof(int));
                        sum += nr;
                }
                int wr_fifo = open("./fifo", O_WRONLY);
                write(wr_fifo, &sum, sizeof(int));
                close(wr_fifo);
                unlink("./fifo");
                close(p[0]);
                wait(0);
        }

        return 0;
}

