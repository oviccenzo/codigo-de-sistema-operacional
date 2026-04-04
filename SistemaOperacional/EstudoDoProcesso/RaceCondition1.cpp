//
// Created by Robert L Resende on 13/06/25.
//

#include "cstdio"
#include "cstdlib"
#include "pthread.h"
#include "unistd.h"
#include "ctime"
#include "cstdlib"

//Macro para gerar número aleatório dentro de um intervalo fechado
#define randnum(min,max) ((rand() % (int)((max) + 1) - (min)) + (min))
#define NUM_THREADS 5
#define ITERACOES 10000

//"Chave de acesso" á região crítica
pthread_mutex_t lock;
int contador = 0; //Variavel compartilhado entre as threads

//Tarefa delegada a cada thread
void *incrementar(void *arg){

    for (int i = 0; i < ITERACOES; ++i) {
        pthread_mutex_lock(&lock); //Bloqueia acesso á variável compartilhado
        contador++;//regiao critica! -> race condition
        pthread_mutex_unlock(&lock);//Libera acesso
    }
    return NULL;
}

int main(){
    //definicao das threads
    pthread_t threads[NUM_THREADS];

    pthread_mutex_init(&lock, NULL);//Inicializa o mutex
    //criando múltiplos threads que acessam a mesma variavel
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i],NULL, incrementar, NULL);
    }
    //Esperando todos os threads terminarem
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    printf("Valor final do contador: %d\t esperado: %d\n", contador, NUM_THREADS * ITERACOES);

    return 0;
}