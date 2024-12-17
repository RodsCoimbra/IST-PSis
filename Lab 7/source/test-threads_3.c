#include <stdio.h>
#include <pthread.h>  
#include <unistd.h> 
#include <stdlib.h>

void * thread_function(void * arg){
    long int r = *(int*)arg;
    int n = 0;
    printf("Start Thread %lu \n", r);
    while(n <1){
        sleep(1);
        n++;
        // printf("inside Thread %lu %d\n", r, n);
    }
    printf("End Thread %lu\n", r);
    return (void *)r;
}

int main(){
    char line[100];
    int n_threads;
    printf("How many threads: ");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &n_threads);
    pthread_t *threads = (pthread_t *)malloc(n_threads * sizeof(pthread_t));

    int i = 0;
    void * value;
    for (int i = 0; i < n_threads; i++) {
        pthread_t thread_id;
        threads[i] = thread_id;
        printf("Creating thread %lu, id = %d\n", thread_id, i);
        pthread_create(&thread_id, NULL,thread_function, &i);
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_join(threads[i], &value);
        printf("Thread %d returned %lu\n", i, (long int)value);
    }
    free(threads);
    exit(0);
}