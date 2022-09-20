/*
 Scrieti 2 programe c, A si B. Programul A va citi doua numare intregi
de la tastatura si va scrie intr-un fifo cel mai mic multiplu comun al
acestora. Programul B va creea 2 procese P1 si P2, P1 va citi multiplul
din fifo-ul mentionat anterior si va calcula divizorii acestuia.
Divizorii vor fi transmis printr-un pipe procesului P2 care ii va afisa
pe ecran.
Numele fifo-ului va fi dat ca argument in linia de comanda in ambele
programe. Programul A va creea fifo-ul si programul B va sterge fifo-ul.
Ambele programe terbuie compilate cu gcc -Wall -g fara erori sau warninguri.
Ambele programe trebuie sa ruleze fara memory leaks, erori de context sau
procese zombie.
*/

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
        if(mkfifo(argv[1], 0600) < 0){
                perror("No fifo?");
                exit(1);
        }
        int wr_fifo = open(argv[1], O_WRONLY);

        int nr1, nr2;
        printf("Number 1: ");
        scanf("%d", &nr1);
        printf("Number 2: ");
        scanf("%d", &nr2);
        int a = nr1, b = nr2;
        while(a % b > 0){
                int r = a % b;
                a = b;
                b = r;
        }
        int cmmmc = nr1 * nr2 / b;
        write(wr_fifo, &cmmmc, sizeof(int));
        close(wr_fifo);

        return 0;
}
