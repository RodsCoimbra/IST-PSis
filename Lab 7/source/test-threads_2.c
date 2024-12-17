#include <stdio.h>
#include <pthread.h>  
#include <unistd.h> 
#include <stdlib.h>

void * thread_function(void * arg){
    int n = 0;
    long int r = random()%100;
    int time = *(int*)arg;
    free(arg);
    printf("Start Thread %lu\n", r);
    while(n < 3){
        sleep(time);
        n++;
        printf("inside Thread %lu %d\n", r, time);
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
    pthread_t* threads = (pthread_t *)malloc(n_threads * sizeof(pthread_t));
    void * value;
    for (int i = 0; i < n_threads; i++) {
        pthread_t thread_id;
        int * timeout = (int*)malloc(sizeof(int));
        *timeout = random()%5;
        pthread_create(&thread_id, NULL,thread_function, timeout);
        threads[i] = thread_id;
    }

    for (int i = 0; i < n_threads; i++) {
        pthread_t thread_id = threads[i];
        pthread_join(thread_id, &value);
        printf("Thread %d returned %lu\n", i, (long int)value);
    }
    free(threads);  
    exit(0);
}