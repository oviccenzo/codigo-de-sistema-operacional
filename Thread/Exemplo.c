#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define NUM_THREADS 10


int sum;
void *runner(void *param);

int main(int argc, char *argv[]) {
    
    pthread_t tid;
    pthread_attr_t attr;

    

    if(argc != 2){
        fprintf(stderr, "Usage: a.out <integer value>\n");
        return -1;
    } 
    if(atoi(argv[1]) < 0){
        fprintf(stderr,"%d must be >= 0\n",argv[1]);
        return -1;
    }
    
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, runner, argv[1]);
    pthread_join(tid, NULL);

    printf("sum = %d\n", sum);

    pthread_t workers[NUM_THREADS];
    
    for(int i = 0; i< NUM_THREADS; i++){
        pthread_join(workers[i], NULL);
    }

    return 0;
}

void *runner(void * param){
    int i, upper = atoi(param);

    sum = 0;
    for(i = 1; i <= upper; i++){
        sum += i;
    }
    pthread_exit(0);
}

