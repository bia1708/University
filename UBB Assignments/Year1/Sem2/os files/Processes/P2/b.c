#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
        int rd_fifo = open(argv[1], O_RDONLY );
        int p[2];
        pipe(p);
        // 0 - read
        // 1 - write
        int f = fork();
        if(f == -1){
                perror("No fork?");
                exit(1);
        } else if(f == 0){
                close(p[0]);
                int cmmmc;
                read(rd_fifo, &cmmmc, sizeof(int));
                int d;
                for(d = 1; d * d <= cmmmc; d++)
                        if(cmmmc % d == 0){
                             int d2 = cmmmc / d;
                             write(p[1], &d, sizeof(int));
                             write(p[1], &d2, sizeof(int));
                        }
                close(p[1]);
                exit(0);
        } else {
                close(p[1]);
                int d;
                while(read(p[0], &d, sizeof(int)))
                        printf("%d ", d);
                close(p[0]);
                wait(0);
        }
        close(rd_fifo);
        unlink(argv[1]);
        return 0;
}
