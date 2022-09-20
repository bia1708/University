#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int* v;
int pos;
pthread_mutex_t* m;
pthread_barrier_t* b;

void* f(void* argv){
        int i, index = *(int*)argv;
        for(i = 0; i < 10; i++){
                pthread_barrier_wait(b);
                pthread_mutex_lock(m);
                v[pos++] = index;
                if(i == 9)
                        printf("index: %d, pos: %d\n", index, pos - 1);
                pthread_mutex_unlock(m);
        }
        return 0;
}

int main(int argc, char* argv[]){
        int i, n = atoi(argv[1]);
        v = malloc(10 * n * sizeof(int));
        pthread_t* t = malloc(n * sizeof(pthread_t));
        int* indexes = malloc(n * sizeof(int));
        m = malloc(sizeof(pthread_mutex_t));
        b = malloc(sizeof(pthread_barrier_t));

        pthread_mutex_init(m, NULL);
        pthread_barrier_init(b, NULL, n);

        for(i = 0; i < n; i++){
                indexes[i] = i;
                pthread_create(&t[i], NULL, f, &indexes[i]);
        }

        for(i = 0; i < n; i++)
                pthread_join(t[i], NULL);

        pthread_mutex_destroy(m);
        pthread_barrier_destroy(b);

        free(b);
        free(m);
        free(v);
        free(t);
        free(indexes);
        return 0;
}
