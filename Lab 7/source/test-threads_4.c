#include <stdio.h>
#include <pthread.h>  
#include <unistd.h> 
#include <stdlib.h>
int n = 0;

void * thread_function(void * arg){
    long int r = random()%100;
    printf("Start Thread %lu\n", r);
    int i = 0;
    while(i <10){
        sleep(1);
        i++;
        n++;
        printf("inside Thread %lu %d\n", r, n);
    }
    printf("End Thread %lu -> %d\n", r, n);
    return (void *)r;
}

int main(){
    char line[100];
    int n_threads;
    printf("How many threads: ");
    fgets(line, 100, stdin);
    sscanf(line, "%d", &n_threads);
    pthread_t thread_id;

    int i = 0;
    while( i < n_threads) {
        pthread_create(&thread_id, NULL,thread_function, NULL);
        i++;
    };
    
    printf("Carregue em enter para terminar\n");
    fgets(line, 100, stdin);
    printf("n = %d\n", n);
    exit(0);
}