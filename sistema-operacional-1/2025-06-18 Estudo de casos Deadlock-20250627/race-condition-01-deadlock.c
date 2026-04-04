#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

// macro para gerar número aleatório dentro de um intervalo fechado
#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))

#define NUM_THREADS 2
#define ITERACOES 100000

// "chave de acesso" à região crítica
pthread_mutex_t first_lock;
pthread_mutex_t second_lock;

int contador = 0; // Variável compartilhada entre as threads

// refactory

// tarefa delegada a cada thread
void* tarefa_one(void* arg) {
	printf("Thread #1 executando.....\n");
    for (int i = 0; i < ITERACOES; i++) {
        pthread_mutex_lock(&first_lock);
		pthread_mutex_lock(&second_lock);
        contador++;
        pthread_mutex_unlock(&second_lock);
		pthread_mutex_unlock(&first_lock);
    }
	printf("Thread #1 saiu da região critica.....\n");
    return NULL;
}

// tarefa delegada a cada thread
void* tarefa_two(void* arg) {
	printf("Thread #2 executando.....\n");
    for (int i = 0; i < ITERACOES; i++) {
		pthread_mutex_lock(&second_lock);
        pthread_mutex_lock(&first_lock);
        contador++;
		pthread_mutex_unlock(&first_lock);
        pthread_mutex_unlock(&second_lock);
    }
	printf("Thread #2 saiu da região critica.....\n");
    return NULL;
}

int main() {

    // definição das threads
    pthread_t threads[NUM_THREADS];
    
    pthread_mutex_init(&first_lock, NULL); // Inicializa o mutex
    pthread_mutex_init(&second_lock, NULL); // Inicializa o mutex

	printf("Processo principal: criando as threads....\n");
    // Criando múltiplos threads que acessam a mesma variável
    for (int i = 0; i < NUM_THREADS; i++) {
        if ( (i % 2) == 0 ) {
			pthread_create(&threads[i], NULL, tarefa_one, NULL);
		} else {
			pthread_create(&threads[i], NULL, tarefa_two, NULL);
		}
    }

	printf("Processo principal: aguardando as threads....\n");
    // Esperando todos os threads terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Valor final do contador: %d\t esperado: %d\n", contador, NUM_THREADS * ITERACOES);
    
    pthread_mutex_destroy(&first_lock); // Destroi o mutex
	pthread_mutex_destroy(&second_lock); // Destroi o mutex

    return 0;
}
