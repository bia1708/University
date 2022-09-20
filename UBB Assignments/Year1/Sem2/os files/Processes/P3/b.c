#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char*argv[]){
        int rd_fifo = open("./fifo", O_RDONLY);
        int sum;
        read(rd_fifo, &sum, sizeof(int));
        printf("%d", sum);
        close(rd_fifo);
        return 0;
}
