#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>

#define N 5

struct status{
    int stat;
    int shop[N];
};

void *shop_take(void *stat_shop){
    struct status *stat = (struct status *)stat_shop;
    int index;
    while(stat->stat > 0){
        index = rand()%(N-1);
        printf("take from %d shop(%d)\n", index, stat->stat);
        stat->stat -= stat->shop[index];
        stat->shop[index] = 0;
        sleep(2);
    }
    pthread_exit(0);
}

void *shop_give(void *stat_shop){
    struct status *stat = (struct status *)stat_shop;
    int index;
    while(stat->stat > 0){
        index = rand()%(N-1);
        printf("give in %d shop\n", index);
        stat->shop[index] += rand()%200 + 400;
        sleep(10);
    }
    pthread_exit(0);
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    pthread_t* threads = (pthread_t*) malloc(N * sizeof(pthread_t));

    struct status *threadData = (struct status*) malloc(sizeof(struct status));

    for(int i = 0; i < N; i++){
        threadData->shop[i] = rand()%200 + 400;
    }
    threadData->stat = 10000;

    for(int i = 0; i < (N-1); i++)
        pthread_create(&(threads[i]), NULL, shop_take, threadData);
    pthread_create(&(threads[N]), NULL, shop_give, threadData);        
    
    for(int i = 0; i < N; i++)
		pthread_join(threads[i], NULL);

    return 0;
}   