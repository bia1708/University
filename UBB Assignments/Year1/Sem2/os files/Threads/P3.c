#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int a, b;
pthread_mutex_t* m;

typedef struct{
        int x, y;
} data;

void* f(void* arg){
        data numbers = *(data*)(arg);
        int i;
        for(i = 0; i < numbers.y; i++){
                pthread_mutex_lock(m);
                a += b + numbers.x;
                b = numbers.x;
                printf("x: %d, y: %d, a: %d, b: %d\n", numbers.x, numbers.y, a, b);
                pthread_mutex_unlock(m);
        }
        return 0;
}

int main(int argc, char* argv[]){
        int i, n = (argc - 1) / 2;
        pthread_t* t = malloc(n * sizeof(pthread_t));
        data* args = malloc(n * sizeof(data));
        m = malloc(sizeof(pthread_mutex_t));

        for(i = 0; i < n; i++){
                args[i].x = atoi(argv[2 * i + 1]);
                args[i].y = atoi(argv[2 * i + 2]);
                pthread_create(&t[i], NULL, f, &args[i]);
        }

        for(i = 0; i < n; i++)
                pthread_join(t[i], NULL);

        free(m);
        free(t);
        free(args);
        return 0;
}
