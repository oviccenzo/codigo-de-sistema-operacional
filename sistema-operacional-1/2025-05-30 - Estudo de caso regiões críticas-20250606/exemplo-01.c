#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define randnum(min, max) ((rand() % (int)(((max) + 1) - (min))) + (min))

void* tarefa_1(void* arg) {
	
	srand(time(NULL));   // Initialization, should only be called once.
	//int r = rand();    // Returns a pseudo-random integer between 0 and RAND_MAX.

    printf("Iniciando a Tarefa 1...\n");
	int s = 0;
    for (int i = 0; i < 5; i++) {
		s = randnum(1, 5);
        printf("Tarefa 1 - Contagem: %d - sleep time: %d (s)\n", i, s);
        sleep( s ); // Simula um atraso de 1 segundo
    }
    printf("Tarefa 1 finalizada!\n");
    return NULL;
}

void* tarefa_2(void* arg) {
	
	srand(time(NULL));

    printf("Iniciando a Tarefa 2...\n");
	int s = 0;
    for (int i = 0; i < 5; i++) {
		s = randnum(1, 8);
        printf("Tarefa 2 - Contagem: %d - sleep time: %d (s)\n", i, s);
        sleep( s ); // Simula um atraso de 1 segundo
    }
    printf("Tarefa 2 finalizada!\n");
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
