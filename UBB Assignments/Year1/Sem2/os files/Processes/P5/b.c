#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
        int i, rd_fifo = open("./fifo", O_RDONLY);
        for(i = 0; i < 5; i++){
                int freq;
                read(rd_fifo, &freq, sizeof(int));
                printf("%d", freq);
        }
        close(rd_fifo);
        unlink("./fifo");
        return 0;
}
