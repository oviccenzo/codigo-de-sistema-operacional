#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// macro para gerar número aleatório dentro de um intervalo fechado
#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))

#define NUM_THREADS 5
#define ITERACOES 100000

int contador = 0; // Variável compartilhada entre as threads

// tarefa delegada a cada thread
void* incrementar(void* arg) {
    for (int i = 0; i < ITERACOES; i++) {
        contador++; // regiao critica! -> Race Condition
    }
    return NULL;
}

int main() {

    // definição das threads
    pthread_t threads[NUM_THREADS];
    
    // Criando múltiplos threads que acessam a mesma variável
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, incrementar, NULL);
    }

    // Esperando todos os threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Valor final do contador: %d\t esperado: %d\n", contador, NUM_THREADS * ITERACOES);

    return 0;
}
