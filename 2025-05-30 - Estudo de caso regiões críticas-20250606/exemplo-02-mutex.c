#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* tarefa_1(void* arg) {
	srand(time(NULL));
    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    printf("Iniciando a Tarefa 1...\n");
	int s = 0;
    for (int i = 0; i < 5; i++) {
		s = randnum(1, 5);
        printf("Tarefa 1 - Contagem: %d - sleep time: %d (s)\n", i, s);
        sleep( s );
    }
    printf("Tarefa 1 finalizada!\n");
    pthread_mutex_unlock(&mutex); // Desbloqueia o mutex
    return NULL;
}

void* tarefa_2(void* arg) {
	srand(time(NULL));
    pthread_mutex_lock(&mutex); // Bloqueia o mutex
    printf("Iniciando a Tarefa 2...\n");
	int s = 0;
    for (int i = 0; i < 5; i++) {
        printf("Tarefa 2 - Contagem: %d - sleep time: %d (s)\n", i, s);
        sleep( s );
    }
    printf("Tarefa 2 finalizada!\n");
    pthread_mutex_unlock(&mutex); // Desbloqueia o mutex
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Cria as threads
	printf("Criando as threads....\n");
    pthread_create(&thread1, NULL, tarefa_1, NULL);
    pthread_create(&thread2, NULL, tarefa_2, NULL);

    // Espera que as threads terminem
	printf("Aguardando as threads terminarem....\n");
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Programa finalizado!\n");
    return 0;
}
