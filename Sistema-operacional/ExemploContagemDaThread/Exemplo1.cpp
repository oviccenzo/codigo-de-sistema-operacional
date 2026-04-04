//
// Created by Robert L Resende on 05/06/25.
//

#include "cstdio"
#include "cstdlib"
#include "unistd.h"
#include "pthread.h"
#include "time.h"

#define randnum(min, max)((rand() % (int)(max) + 1) - (min) +(min))

void *tarefa1(void* arg){

    srand(time(NULL));
    //int r = rand();
    printf("Iniciando a tarefa 1...\n");
    int s = 0;
    for (int i = 0; i < 5; i++) {
        s = randnum(1,5);
        printf("Tarefa 1 - Contagem %d - sleep time %d: (s)\n",i,s);
        sleep(s);
    }
    printf("Tarefa 1 finalizado!\n");
    return NULL;
}

void *tarefa2(void* arg){
    srand(time(NULL));
    //int r = rand();
    printf("Iniciando a tarefa 2...\n");
    int s = 0;
    for (int i = 0; i < 5; ++i) {
        s = randnum(1,8);
        printf("Tarefa 2 - Contagem %d - sleep time %d: (s)\n",i,s);
    }
    return NULL;
}

int main(){

    pthread_t thread1,thread2;
    printf("Criando as thread....\n");
    pthread_create(&thread1, NULL, tarefa1, NULL);
    pthread_create(&thread2, NULL, tarefa2, NULL);

    printf("Aguardando as threads terminarem...\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Programa finalizados");
    return 0;
}