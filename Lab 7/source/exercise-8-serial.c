#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

int *rand_num_array;

#define LIMIT 100000000

void *n_mult(void *n)
{
    int multiple = *(int *)n;
    long int c = 0;
    for (int i = 0; i < LIMIT; i++)
    {
        if (rand_num_array[i] % multiple == 0)
            c++;
    }
    return (void*) c;
}

int main()
{
    srand(0);
    rand_num_array = calloc(LIMIT, sizeof(int));
    for (int i = 0; i < LIMIT; i++)
    {
        rand_num_array[i] = random();
    }
    int multiples[] = {2, 3, 5, 7, 11};
    int len = sizeof(multiples) / sizeof(int);
    pthread_t* threads = (pthread_t *)malloc(len * sizeof(pthread_t));
    pthread_t thread_id;
    void * counter;
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&thread_id, NULL, n_mult, &multiples[i]);
        threads[i] = thread_id;
    }
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], &counter);
        printf("Number of multiples of %d found: %ld\n", multiples[i], (long int)counter);
    }
    exit(0);
}