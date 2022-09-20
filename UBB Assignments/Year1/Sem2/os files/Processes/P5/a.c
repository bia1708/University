/*
   Write 2 c programs, A and B. A will create 2 prcesses p1 and p2. p1 will
   read from the standard input (keyboard) the path to a file f, f can have any number of characters any number of times.
   p1 will send to p2, via pipe, the path.
   p2 will send to B, via fifo, 5 numbers, each representing the frequency of a large
   vowel (A,E,I,O,U) found in the file. B will display the numbers on the
   standard output (the console).
   The source file must be compiled using gcc with -Wall -g options WITHOUT WARNINGS OR SYNTAX ERRORS!!!
   Memory leacks and zombie processes are not allowed.
   */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]){
        if(mkfifo("./fifo", 0600) < 0){
                perror("soijf");
                exit(1);
        }

        int wr_fifo = open("./fifo", O_WRONLY);
        int p[2];
        pipe(p);
        int f1 = fork();
        if(f1 == -1){
                perror("doiafcjiosdf");
                exit(1);
        } else if(f1 == 0){
                close(p[0]);
                close(wr_fifo);
                char filename[50];
                scanf("%s", filename);
                int length = strlen(filename);
                write(p[1], &length, sizeof(int));
                write(p[1], filename, sizeof(char) * (length + 1));
                close(p[1]);
                printf("here\n");
                exit(0);
        }
        printf("ahsf\n");
        fflush(stdout);
        int f2 = fork();
        if(f2 == -1){
                perror("sudhofihsd");
                exit(1);
        } else if(f2 == 0){
                printf("jshdf");

                fflush(stdout);
                close(p[1]);
                char filename[50];
                int length;
                read(p[0], &length, sizeof(int));
                read(p[0], filename, sizeof(char) * (length + 1));
                FILE* file = fopen(filename, "r");
                int fr[6] = {0};
                char c;
                while(fscanf(file, "%c", &c)){
                        if(c == 'A')
                             fr[0]++;
                        else if(c == 'E')
                             fr[1]++;
                        else if(c == 'I')
                             fr[2]++;
                        else if(c == 'O')
                             fr[3]++;
                        else if(c == 'U')
                             fr[4]++;
                }
                int i;
                for(i = 0; i < 5; i++)
                        write(wr_fifo, &fr[i], sizeof(int));
                close(wr_fifo);
                fclose(file);
                close(p[0]);
                exit(0);
        }
        close(wr_fifo);
        close(p[0]);
        close(p[1]);

        wait(0);
        wait(0);

        return 0;
}
