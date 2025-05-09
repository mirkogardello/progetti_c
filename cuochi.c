#include    <unistd.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <pthread.h>
#include    <string.h>
#include    <time.h>
#include    <semaphore.h>
#define NUMERO_THREADS 10
#define NUMERO_FORNELLI 3
#define NUMERO_PIATTI 5
char ** Menu;
FILE * f;
sem_t sem;
void* cuoco(void*arg)
{
    sem_wait(&sem);
    int x = (int)arg;
    int n = rand()%NUMERO_PIATTI;

    printf("Cuoco %d sta preparando %s\n", x, Menu[n]);
    fprintf(f, "Cuoco %d sta preparando %s\n", x, Menu[n]);
    sleep(1);
    sem_post(&sem);
    return NULL;
}

int main()
{
    pthread_t threads[NUMERO_THREADS];
    srand(time(NULL));
    Menu = malloc (NUMERO_PIATTI*sizeof(char*));
    Menu[0] = "Pasta";
    Menu[1] = "Pizza";
    Menu[2] = "Carne";
    Menu[3] = "Pesce";
    Menu[4] = "Dolce";
    printf("Piatti disponibili:\n");
    for(int i=0;i<NUMERO_PIATTI;i++)
    {
        printf("%s ", Menu[i]);
    }
    printf("\n\n");

    f = fopen("fornelli.txt", "a");
    sem_init(&sem, 0, NUMERO_FORNELLI);
    for(int i=0;i<NUMERO_THREADS;i++)
    {
        
        pthread_create(&threads[i], NULL, cuoco, (void*)i);
    }
    for(int i=0;i<NUMERO_THREADS;i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("Tutti i cuochi hanno finito di cucinare\n");
    fclose(f);
    sem_destroy(&sem);
    return 0;
}