#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
        int rd_fifo = open("./fifo", O_RDONLY);
        int c;
        read(rd_fifo, &c, sizeof(char));
        printf("ASCII: %d", c);
        close(rd_fifo);
        unlink("./fifo");
        return 0;
}
