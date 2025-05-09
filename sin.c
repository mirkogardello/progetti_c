#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>
#define NUMERO_THREADS 5
pthread_mutex_t lock;
sem_t sem;
int contatoreCondiviso =0;
void * fase1(void * arg)
{
    sem_wait(&sem);
    int x = *(int*)arg;
    printf("thead %d sta eseuendo la fase 1\n", x);
    sleep(.5);
    sem_post(&sem);
    return NULL;
}


void * fase2(void * arg)
{
    pthread_mutex_lock(&lock);
    int x = *(int*)arg;

    printf("thead %d sta eseguendo la fase 2, il contatore modificato è: %d\n", x, ++contatoreCondiviso );
    sleep(.5);
    pthread_mutex_unlock(&lock);
    return NULL;
}
int main()
{
    srand(time(NULL));
    pthread_t threads[NUMERO_THREADS];
    sem_init(&sem, 0, 2);
    for(int i=0;i<NUMERO_THREADS;i++)
    {
        pthread_create(&threads[i], NULL, fase1, (void*)&i);
    }
    for(int i=0;i<NUMERO_THREADS;i++)
    {
        pthread_join(threads[i], NULL);
    }
    sem_destroy(&sem);



    printf("\n\nComincia la fase 2\n");

    pthread_mutex_init(&lock, NULL);
    for(int i=0;i<NUMERO_THREADS;i++)
    {
        pthread_create(&threads[i], NULL, fase2, (void*)&i);
    }
    for(int i=0;i<NUMERO_THREADS;i++)
    {
        pthread_join(threads[i], NULL);
    }


    pthread_mutex_destroy(&lock);
    printf("Contatore finale: %d\n", contatoreCondiviso);
    return 0;
}