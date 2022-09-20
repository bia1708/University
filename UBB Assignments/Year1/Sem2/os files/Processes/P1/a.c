#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char **argv){
        if (mkfifo("./myfifo", 0600) < 0) {
                perror("Error on creating the fifo");
                return 0;
        }

        printf("Start scanf\n");
        int wr = open("./myfifo", O_WRONLY);

        char filename[30];
        printf("Start scanf\n");
        scanf("%s", filename);
        printf("Done reading filename: %s\n", filename);

        FILE *f = fopen(filename, "r");
        char c;
        while (fscanf(f, "%c", &c) == 1) {
                if ('0' <= c && c <= '9') {
                        write(wr, &c, sizeof(char));
                }
        }
        fclose(f);
        close(wr);
        return 0;
}
