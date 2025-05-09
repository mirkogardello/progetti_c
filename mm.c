#include    <unistd.h>
#include    <stdio.h>
#include    <stdlib.h>
#include    <pthread.h>
#include    <string.h>
#include    <time.h>
pthread_mutex_t lock;
#define NUMERO_THREADS 10
#define GUSTI 3
char ** merendineDipsonibili;
FILE * f;

void * tf(void * arg)
{
    pthread_mutex_lock(&lock);
    int x = (int)arg;
    int scelta = rand() % GUSTI;
    printf("Scelta del thread %d : %s\n", x, merendineDipsonibili[scelta]);
    fprintf(f, "Scelta del thread %d : %s\n", x, merendineDipsonibili[scelta]);
    sleep(1);
    pthread_mutex_unlock(&lock);
    return  NULL;
}




int main()
{
    srand(time(NULL));
    merendineDipsonibili = malloc(GUSTI*sizeof(char*));
    merendineDipsonibili[0] = "Oreo";
    merendineDipsonibili[1] = "Oro ciok";
    merendineDipsonibili[2] = "Paradiso";
    f = fopen("merendine.txt", "a");

    printf("Merendine disponibili:\n");
    for(int i=0;i<GUSTI;i++)
    {
        printf("%s ", merendineDipsonibili[i]);
    }
    printf("\n\n");
    pthread_mutex_init(&lock, NULL);
    pthread_t threads[NUMERO_THREADS];
    for(int i=0;i<NUMERO_THREADS;i++)
    {
        pthread_create(&threads[i], NULL, tf, (void*)i);
    }
    for(int i=0;i<NUMERO_THREADS;i++)
    {
        pthread_join(threads[i], NULL);
    }
    fclose(f);
    pthread_mutex_destroy(&lock);

    return 0;
}