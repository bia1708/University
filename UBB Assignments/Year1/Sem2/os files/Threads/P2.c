/*
Scrieti un program C care primeste ca si argumente in linia de comanda oricate fisiere. Fiecare fisier va cantine doua numere intregi a inter 1 si 100 si b intre 1000 si 100000. Prgramul va avea n variabile globale, n find numarul de fisiere date ca argument in linia de comanda. Programu va crea cate doua thread-uri x si y pentru fiecare fisier primit ca argument, Fiecare pereche de thread-uri x si y va primi ca argument un fisier dat ca argument, thread-ul x va citi numarul a si b din fisier si va adauga valoarea lui a la variabila globala asociata acestuia pana cand variabila globala va depasi valoarea lui b, moment in care x va trimite un semnal lui y si y va afisa pe ecran valoarea variabilei globale.
*/


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int* vars;
int* finished;

typedef struct{
        char* filename;
        int index;
}data;

pthread_mutex_t** m;
pthread_cond_t** c;

void* fx(void* argv){
        data arg = *(data*)argv;
        FILE* f = fopen(arg.filename, "r");
        int a, b;
        fscanf(f, "%d", &a);
        fscanf(f, "%d", &b);
        fclose(f);

        while(vars[arg.index] < b)
                vars[arg.index] += a;

        pthread_mutex_lock(m[arg.index]);
        finished[arg.index] = 1;
        pthread_cond_signal(c[arg.index]);
        pthread_mutex_unlock(m[arg.index]);

        return 0;
}

void* fy(void* argv){
        data arg = *(data*) argv;
        while(1){
                pthread_mutex_lock(m[arg.index]);
                if(finished[arg.index] == 1)
                        break;
                pthread_cond_wait(c[arg.index], m[arg.index]);
                pthread_mutex_unlock(m[arg.index]);
        }
        printf("%d\n", vars[arg.index]);
        pthread_mutex_unlock(m[arg.index]);
        return 0;
}

int main(int argc, char* argv[]){
        int i, n = argc - 1;
        vars = malloc(n * sizeof(int));
        pthread_t* tx = malloc(sizeof(pthread_t) * n);
        pthread_t* ty = malloc(sizeof(pthread_t) * n);

        finished = malloc(sizeof(int) * n);

        m = malloc(sizeof(pthread_mutex_t*) * n);
        for(i = 0; i < n; i++){
                m[i] = malloc(sizeof(pthread_mutex_t));
                pthread_mutex_init(m[i], NULL);
        }

        c = malloc(sizeof(pthread_cond_t*) * n);
        for(i = 0; i < n; i++){
                c[i] = malloc(sizeof(pthread_cond_t));
                pthread_cond_init(c[i], NULL);
        }

        data* argsx = malloc(sizeof(data) * n);
        data* argsy = malloc(sizeof(data) * n);

        for(i = 0; i < n; i++){
                argsx[i].index = i;
                argsy[i].index = i;
                argsx[i].filename = argv[i + 1];
                argsy[i].filename = argv[i + 1];
                finished[i] = 0;
                pthread_create(&tx[i], NULL, fx, &argsx[i]);
                pthread_create(&ty[i], NULL, fy, &argsy[i]);
        }

        for(i = 0; i < n; i++){
                pthread_join(tx[i], NULL);
                pthread_join(ty[i], NULL);
        }

        for(i = 0; i < n; i++)
                pthread_cond_destroy(c[i]);

        for(i = 0; i < n; i++)
                free(c[i]);
        free(c);

        for(i = 0; i < n; i++)
                pthread_mutex_destroy(m[i]);

        for(i = 0; i < n; i++)
                free(m[i]);
        free(finished);
        free(m);
        free(argsx);
        free(argsy);
        free(vars);
        free(tx);
        free(ty);
        return 0;
}
