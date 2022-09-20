#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char **argv){
        int p[2];
        pipe(p);
        int f = fork();
        if (f == -1) {
                perror("Fail on fork");
                return 0;
        } else if (f == 0) {
                // p1
                close(p[0]);
                int rd = open("./myfifo", O_RDONLY);
                char c;
                int sum = 0;
                while (read(rd, &c, sizeof(char)) > 0) {
                        sum += c - '0';
                }
                write(p[1], &sum, sizeof(int));
                close(p[1]);
                close(rd);
                exit(0);
        } else {
                // parent
                close(p[1]);
                int ff;
                if ((ff = fork()) < 0) {
                        perror("Fail on second fork");
                } else if (ff == 0) {
                        // p2
                        int sum;
                        read(p[0], &sum, sizeof(int));
                        close(p[0]);

                        for (int d = 1; d <= sum; ++d) {
                             if (sum % d == 0) {
                                printf("%d ", d);
                             }
                        }
                        exit(0);
                }
        }
        close(p[0]);
        wait(0);
        wait(0);
        unlink("myfifo");
}
